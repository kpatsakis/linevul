static int srpt_cm_req_recv(struct ib_cm_id *cm_id,
			    struct ib_cm_req_event_param *param,
			    void *private_data)
{
	struct srpt_device *sdev = cm_id->context;
	struct srpt_port *sport = &sdev->port[param->port - 1];
	struct srp_login_req *req;
	struct srp_login_rsp *rsp;
	struct srp_login_rej *rej;
	struct ib_cm_rep_param *rep_param;
	struct srpt_rdma_ch *ch, *tmp_ch;
	struct se_node_acl *se_acl;
	u32 it_iu_len;
	int i, ret = 0;
	unsigned char *p;

	WARN_ON_ONCE(irqs_disabled());

	if (WARN_ON(!sdev || !private_data))
		return -EINVAL;

	req = (struct srp_login_req *)private_data;

	it_iu_len = be32_to_cpu(req->req_it_iu_len);

	pr_info("Received SRP_LOGIN_REQ with i_port_id 0x%llx:0x%llx,"
		" t_port_id 0x%llx:0x%llx and it_iu_len %d on port %d"
		" (guid=0x%llx:0x%llx)\n",
		be64_to_cpu(*(__be64 *)&req->initiator_port_id[0]),
		be64_to_cpu(*(__be64 *)&req->initiator_port_id[8]),
		be64_to_cpu(*(__be64 *)&req->target_port_id[0]),
		be64_to_cpu(*(__be64 *)&req->target_port_id[8]),
		it_iu_len,
		param->port,
		be64_to_cpu(*(__be64 *)&sdev->port[param->port - 1].gid.raw[0]),
		be64_to_cpu(*(__be64 *)&sdev->port[param->port - 1].gid.raw[8]));

	rsp = kzalloc(sizeof *rsp, GFP_KERNEL);
	rej = kzalloc(sizeof *rej, GFP_KERNEL);
	rep_param = kzalloc(sizeof *rep_param, GFP_KERNEL);

	if (!rsp || !rej || !rep_param) {
		ret = -ENOMEM;
		goto out;
	}

	if (it_iu_len > srp_max_req_size || it_iu_len < 64) {
		rej->reason = cpu_to_be32(
			      SRP_LOGIN_REJ_REQ_IT_IU_LENGTH_TOO_LARGE);
		ret = -EINVAL;
		pr_err("rejected SRP_LOGIN_REQ because its"
		       " length (%d bytes) is out of range (%d .. %d)\n",
		       it_iu_len, 64, srp_max_req_size);
		goto reject;
	}

	if (!sport->enabled) {
		rej->reason = cpu_to_be32(
			      SRP_LOGIN_REJ_INSUFFICIENT_RESOURCES);
		ret = -EINVAL;
		pr_err("rejected SRP_LOGIN_REQ because the target port"
		       " has not yet been enabled\n");
		goto reject;
	}

	if ((req->req_flags & SRP_MTCH_ACTION) == SRP_MULTICHAN_SINGLE) {
		rsp->rsp_flags = SRP_LOGIN_RSP_MULTICHAN_NO_CHAN;

		spin_lock_irq(&sdev->spinlock);

		list_for_each_entry_safe(ch, tmp_ch, &sdev->rch_list, list) {
			if (!memcmp(ch->i_port_id, req->initiator_port_id, 16)
			    && !memcmp(ch->t_port_id, req->target_port_id, 16)
			    && param->port == ch->sport->port
			    && param->listen_id == ch->sport->sdev->cm_id
			    && ch->cm_id) {
				enum rdma_ch_state ch_state;

				ch_state = srpt_get_ch_state(ch);
				if (ch_state != CH_CONNECTING
				    && ch_state != CH_LIVE)
					continue;

				/* found an existing channel */
				pr_debug("Found existing channel %s"
					 " cm_id= %p state= %d\n",
					 ch->sess_name, ch->cm_id, ch_state);

				__srpt_close_ch(ch);

				rsp->rsp_flags =
					SRP_LOGIN_RSP_MULTICHAN_TERMINATED;
			}
		}

		spin_unlock_irq(&sdev->spinlock);

	} else
		rsp->rsp_flags = SRP_LOGIN_RSP_MULTICHAN_MAINTAINED;

	if (*(__be64 *)req->target_port_id != cpu_to_be64(srpt_service_guid)
	    || *(__be64 *)(req->target_port_id + 8) !=
	       cpu_to_be64(srpt_service_guid)) {
		rej->reason = cpu_to_be32(
			      SRP_LOGIN_REJ_UNABLE_ASSOCIATE_CHANNEL);
		ret = -ENOMEM;
		pr_err("rejected SRP_LOGIN_REQ because it"
		       " has an invalid target port identifier.\n");
		goto reject;
	}

	ch = kzalloc(sizeof *ch, GFP_KERNEL);
	if (!ch) {
		rej->reason = cpu_to_be32(
			      SRP_LOGIN_REJ_INSUFFICIENT_RESOURCES);
		pr_err("rejected SRP_LOGIN_REQ because no memory.\n");
		ret = -ENOMEM;
		goto reject;
	}

	INIT_WORK(&ch->release_work, srpt_release_channel_work);
	memcpy(ch->i_port_id, req->initiator_port_id, 16);
	memcpy(ch->t_port_id, req->target_port_id, 16);
	ch->sport = &sdev->port[param->port - 1];
	ch->cm_id = cm_id;
	/*
	 * Avoid QUEUE_FULL conditions by limiting the number of buffers used
	 * for the SRP protocol to the command queue size.
	 */
	ch->rq_size = SRPT_RQ_SIZE;
	spin_lock_init(&ch->spinlock);
	ch->state = CH_CONNECTING;
	INIT_LIST_HEAD(&ch->cmd_wait_list);
	ch->rsp_size = ch->sport->port_attrib.srp_max_rsp_size;

	ch->ioctx_ring = (struct srpt_send_ioctx **)
		srpt_alloc_ioctx_ring(ch->sport->sdev, ch->rq_size,
				      sizeof(*ch->ioctx_ring[0]),
				      ch->rsp_size, DMA_TO_DEVICE);
	if (!ch->ioctx_ring)
		goto free_ch;

	INIT_LIST_HEAD(&ch->free_list);
	for (i = 0; i < ch->rq_size; i++) {
		ch->ioctx_ring[i]->ch = ch;
		list_add_tail(&ch->ioctx_ring[i]->free_list, &ch->free_list);
	}

	ret = srpt_create_ch_ib(ch);
	if (ret) {
		rej->reason = cpu_to_be32(
			      SRP_LOGIN_REJ_INSUFFICIENT_RESOURCES);
		pr_err("rejected SRP_LOGIN_REQ because creating"
		       " a new RDMA channel failed.\n");
		goto free_ring;
	}

	ret = srpt_ch_qp_rtr(ch, ch->qp);
	if (ret) {
		rej->reason = cpu_to_be32(SRP_LOGIN_REJ_INSUFFICIENT_RESOURCES);
		pr_err("rejected SRP_LOGIN_REQ because enabling"
		       " RTR failed (error code = %d)\n", ret);
		goto destroy_ib;
	}

	/*
	 * Use the initator port identifier as the session name, when
	 * checking against se_node_acl->initiatorname[] this can be
	 * with or without preceeding '0x'.
	 */
	snprintf(ch->sess_name, sizeof(ch->sess_name), "0x%016llx%016llx",
			be64_to_cpu(*(__be64 *)ch->i_port_id),
			be64_to_cpu(*(__be64 *)(ch->i_port_id + 8)));

	pr_debug("registering session %s\n", ch->sess_name);
	p = &ch->sess_name[0];

	ch->sess = transport_init_session(TARGET_PROT_NORMAL);
	if (IS_ERR(ch->sess)) {
		rej->reason = cpu_to_be32(
				SRP_LOGIN_REJ_INSUFFICIENT_RESOURCES);
		pr_debug("Failed to create session\n");
		goto destroy_ib;
	}

try_again:
	se_acl = core_tpg_get_initiator_node_acl(&sport->port_tpg_1, p);
	if (!se_acl) {
		pr_info("Rejected login because no ACL has been"
			" configured yet for initiator %s.\n", ch->sess_name);
		/*
		 * XXX: Hack to retry of ch->i_port_id without leading '0x'
		 */
		if (p == &ch->sess_name[0]) {
			p += 2;
			goto try_again;
		}
		rej->reason = cpu_to_be32(
				SRP_LOGIN_REJ_CHANNEL_LIMIT_REACHED);
		transport_free_session(ch->sess);
		goto destroy_ib;
	}
	ch->sess->se_node_acl = se_acl;

	transport_register_session(&sport->port_tpg_1, se_acl, ch->sess, ch);

	pr_debug("Establish connection sess=%p name=%s cm_id=%p\n", ch->sess,
		 ch->sess_name, ch->cm_id);

	/* create srp_login_response */
	rsp->opcode = SRP_LOGIN_RSP;
	rsp->tag = req->tag;
	rsp->max_it_iu_len = req->req_it_iu_len;
	rsp->max_ti_iu_len = req->req_it_iu_len;
	ch->max_ti_iu_len = it_iu_len;
	rsp->buf_fmt = cpu_to_be16(SRP_BUF_FORMAT_DIRECT
				   | SRP_BUF_FORMAT_INDIRECT);
	rsp->req_lim_delta = cpu_to_be32(ch->rq_size);
	atomic_set(&ch->req_lim, ch->rq_size);
	atomic_set(&ch->req_lim_delta, 0);

	/* create cm reply */
	rep_param->qp_num = ch->qp->qp_num;
	rep_param->private_data = (void *)rsp;
	rep_param->private_data_len = sizeof *rsp;
	rep_param->rnr_retry_count = 7;
	rep_param->flow_control = 1;
	rep_param->failover_accepted = 0;
	rep_param->srq = 1;
	rep_param->responder_resources = 4;
	rep_param->initiator_depth = 4;

	ret = ib_send_cm_rep(cm_id, rep_param);
	if (ret) {
		pr_err("sending SRP_LOGIN_REQ response failed"
		       " (error code = %d)\n", ret);
		goto release_channel;
	}

	spin_lock_irq(&sdev->spinlock);
	list_add_tail(&ch->list, &sdev->rch_list);
	spin_unlock_irq(&sdev->spinlock);

	goto out;

release_channel:
	srpt_set_ch_state(ch, CH_RELEASING);
	transport_deregister_session_configfs(ch->sess);
	transport_deregister_session(ch->sess);
	ch->sess = NULL;

destroy_ib:
	srpt_destroy_ch_ib(ch);

free_ring:
	srpt_free_ioctx_ring((struct srpt_ioctx **)ch->ioctx_ring,
			     ch->sport->sdev, ch->rq_size,
			     ch->rsp_size, DMA_TO_DEVICE);
free_ch:
	kfree(ch);

reject:
	rej->opcode = SRP_LOGIN_REJ;
	rej->tag = req->tag;
	rej->buf_fmt = cpu_to_be16(SRP_BUF_FORMAT_DIRECT
				   | SRP_BUF_FORMAT_INDIRECT);

	ib_send_cm_rej(cm_id, IB_CM_REJ_CONSUMER_DEFINED, NULL, 0,
			     (void *)rej, sizeof *rej);

out:
	kfree(rep_param);
	kfree(rsp);
	kfree(rej);

	return ret;
}
