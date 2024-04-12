static void srpt_mad_recv_handler(struct ib_mad_agent *mad_agent,
				  struct ib_mad_send_buf *send_buf,
				  struct ib_mad_recv_wc *mad_wc)
{
	struct srpt_port *sport = (struct srpt_port *)mad_agent->context;
	struct ib_ah *ah;
	struct ib_mad_send_buf *rsp;
	struct ib_dm_mad *dm_mad;

	if (!mad_wc || !mad_wc->recv_buf.mad)
		return;

	ah = ib_create_ah_from_wc(mad_agent->qp->pd, mad_wc->wc,
				  mad_wc->recv_buf.grh, mad_agent->port_num);
	if (IS_ERR(ah))
		goto err;

	BUILD_BUG_ON(offsetof(struct ib_dm_mad, data) != IB_MGMT_DEVICE_HDR);

	rsp = ib_create_send_mad(mad_agent, mad_wc->wc->src_qp,
				 mad_wc->wc->pkey_index, 0,
				 IB_MGMT_DEVICE_HDR, IB_MGMT_DEVICE_DATA,
				 GFP_KERNEL,
				 IB_MGMT_BASE_VERSION);
	if (IS_ERR(rsp))
		goto err_rsp;

	rsp->ah = ah;

	dm_mad = rsp->mad;
	memcpy(dm_mad, mad_wc->recv_buf.mad, sizeof *dm_mad);
	dm_mad->mad_hdr.method = IB_MGMT_METHOD_GET_RESP;
	dm_mad->mad_hdr.status = 0;

	switch (mad_wc->recv_buf.mad->mad_hdr.method) {
	case IB_MGMT_METHOD_GET:
		srpt_mgmt_method_get(sport, mad_wc->recv_buf.mad, dm_mad);
		break;
	case IB_MGMT_METHOD_SET:
		dm_mad->mad_hdr.status =
		    cpu_to_be16(DM_MAD_STATUS_UNSUP_METHOD_ATTR);
		break;
	default:
		dm_mad->mad_hdr.status =
		    cpu_to_be16(DM_MAD_STATUS_UNSUP_METHOD);
		break;
	}

	if (!ib_post_send_mad(rsp, NULL)) {
		ib_free_recv_mad(mad_wc);
		/* will destroy_ah & free_send_mad in send completion */
		return;
	}

	ib_free_send_mad(rsp);

err_rsp:
	ib_destroy_ah(ah);
err:
	ib_free_recv_mad(mad_wc);
}
