int ib_send_cm_rep(struct ib_cm_id *cm_id,
		   struct ib_cm_rep_param *param)
{
	struct cm_id_private *cm_id_priv;
	struct ib_mad_send_buf *msg;
	struct cm_rep_msg *rep_msg;
	unsigned long flags;
	int ret;

	if (param->private_data &&
	    param->private_data_len > IB_CM_REP_PRIVATE_DATA_SIZE)
		return -EINVAL;

	cm_id_priv = container_of(cm_id, struct cm_id_private, id);
	spin_lock_irqsave(&cm_id_priv->lock, flags);
	if (cm_id->state != IB_CM_REQ_RCVD &&
	    cm_id->state != IB_CM_MRA_REQ_SENT) {
		ret = -EINVAL;
		goto out;
	}

	ret = cm_alloc_msg(cm_id_priv, &msg);
	if (ret)
		goto out;

	rep_msg = (struct cm_rep_msg *) msg->mad;
	cm_format_rep(rep_msg, cm_id_priv, param);
	msg->timeout_ms = cm_id_priv->timeout_ms;
	msg->context[1] = (void *) (unsigned long) IB_CM_REP_SENT;

	ret = ib_post_send_mad(msg, NULL);
	if (ret) {
		spin_unlock_irqrestore(&cm_id_priv->lock, flags);
		cm_free_msg(msg);
		return ret;
	}

	cm_id->state = IB_CM_REP_SENT;
	cm_id_priv->msg = msg;
	cm_id_priv->initiator_depth = param->initiator_depth;
	cm_id_priv->responder_resources = param->responder_resources;
	cm_id_priv->rq_psn = cm_rep_get_starting_psn(rep_msg);
	cm_id_priv->local_qpn = cpu_to_be32(param->qp_num & 0xFFFFFF);

out:	spin_unlock_irqrestore(&cm_id_priv->lock, flags);
	return ret;
}
