static void srpt_queue_response(struct se_cmd *cmd)
{
	struct srpt_rdma_ch *ch;
	struct srpt_send_ioctx *ioctx;
	enum srpt_command_state state;
	unsigned long flags;
	int ret;
	enum dma_data_direction dir;
	int resp_len;
	u8 srp_tm_status;

	ioctx = container_of(cmd, struct srpt_send_ioctx, cmd);
	ch = ioctx->ch;
	BUG_ON(!ch);

	spin_lock_irqsave(&ioctx->spinlock, flags);
	state = ioctx->state;
	switch (state) {
	case SRPT_STATE_NEW:
	case SRPT_STATE_DATA_IN:
		ioctx->state = SRPT_STATE_CMD_RSP_SENT;
		break;
	case SRPT_STATE_MGMT:
		ioctx->state = SRPT_STATE_MGMT_RSP_SENT;
		break;
	default:
		WARN(true, "ch %p; cmd %d: unexpected command state %d\n",
			ch, ioctx->ioctx.index, ioctx->state);
		break;
	}
	spin_unlock_irqrestore(&ioctx->spinlock, flags);

	if (unlikely(transport_check_aborted_status(&ioctx->cmd, false)
		     || WARN_ON_ONCE(state == SRPT_STATE_CMD_RSP_SENT))) {
		atomic_inc(&ch->req_lim_delta);
		srpt_abort_cmd(ioctx);
		return;
	}

	dir = ioctx->cmd.data_direction;

	/* For read commands, transfer the data to the initiator. */
	if (dir == DMA_FROM_DEVICE && ioctx->cmd.data_length &&
	    !ioctx->queue_status_only) {
		ret = srpt_xfer_data(ch, ioctx);
		if (ret) {
			pr_err("xfer_data failed for tag %llu\n",
			       ioctx->cmd.tag);
			return;
		}
	}

	if (state != SRPT_STATE_MGMT)
		resp_len = srpt_build_cmd_rsp(ch, ioctx, ioctx->cmd.tag,
					      cmd->scsi_status);
	else {
		srp_tm_status
			= tcm_to_srp_tsk_mgmt_status(cmd->se_tmr_req->response);
		resp_len = srpt_build_tskmgmt_rsp(ch, ioctx, srp_tm_status,
						 ioctx->cmd.tag);
	}
	ret = srpt_post_send(ch, ioctx, resp_len);
	if (ret) {
		pr_err("sending cmd response failed for tag %llu\n",
		       ioctx->cmd.tag);
		srpt_unmap_sg_to_ib_sge(ch, ioctx);
		srpt_set_cmd_state(ioctx, SRPT_STATE_DONE);
		target_put_sess_cmd(&ioctx->cmd);
	}
}
