void mca_ccb_snd_rsp(tMCA_CCB* p_ccb, tMCA_CCB_EVT* p_data) {
  tMCA_CCB_MSG* p_msg = (tMCA_CCB_MSG*)p_data;
 uint8_t *p, *p_start;
  BT_HDR* p_pkt = (BT_HDR*)osi_malloc(MCA_CTRL_MTU + sizeof(BT_HDR));

  MCA_TRACE_DEBUG("%s cong=%d req=%d", __func__, p_ccb->cong, p_msg->op_code);
 /* assume that API functions verified the parameters */

  p_pkt->offset = L2CAP_MIN_OFFSET;
  p = p_start = (uint8_t*)(p_pkt + 1) + L2CAP_MIN_OFFSET;
 *p++ = p_msg->op_code;
 *p++ = p_msg->rsp_code;
  UINT16_TO_BE_STREAM(p, p_msg->mdl_id);
 if (p_msg->rsp_code == MCA_RSP_SUCCESS) {
 if (p_msg->op_code == MCA_OP_MDL_CREATE_RSP) {
 *p++ = p_msg->param;
 }
 if (p_msg->op_code == MCA_OP_MDL_CREATE_RSP ||
        p_msg->op_code == MCA_OP_MDL_RECONNECT_RSP) {
      mca_dcb_by_hdl(p_msg->dcb_idx);
      BTM_SetSecurityLevel(false, "", BTM_SEC_SERVICE_MCAP_DATA,
                           p_ccb->sec_mask, p_ccb->p_rcb->reg.data_psm,
                           BTM_SEC_PROTO_MCA, p_msg->dcb_idx);
      p_ccb->status = MCA_CCB_STAT_PENDING;
 /* set p_tx_req to block API_REQ/API_RSP before DL is up */
      osi_free_and_reset((void**)&p_ccb->p_tx_req);
      p_ccb->p_tx_req = p_ccb->p_rx_msg;
      p_ccb->p_rx_msg = NULL;
      p_ccb->p_tx_req->dcb_idx = p_msg->dcb_idx;
 }
 }

  osi_free_and_reset((void**)&p_ccb->p_rx_msg);
  p_pkt->len = p - p_start;
  L2CA_DataWrite(p_ccb->lcid, p_pkt);
}
