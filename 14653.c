void smp_proc_sec_req(tSMP_CB* p_cb, tSMP_INT_DATA* p_data) {
  tBTM_LE_AUTH_REQ auth_req = *(tBTM_LE_AUTH_REQ*)p_data;
  tBTM_BLE_SEC_REQ_ACT sec_req_act;

  SMP_TRACE_DEBUG("%s: auth_req=0x%x", __func__, auth_req);

  p_cb->cb_evt = 0;

  btm_ble_link_sec_check(p_cb->pairing_bda, auth_req, &sec_req_act);

  SMP_TRACE_DEBUG("%s: sec_req_act=0x%x", __func__, sec_req_act);

 switch (sec_req_act) {
 case BTM_BLE_SEC_REQ_ACT_ENCRYPT:
      SMP_TRACE_DEBUG("%s: BTM_BLE_SEC_REQ_ACT_ENCRYPT", __func__);
      smp_sm_event(p_cb, SMP_ENC_REQ_EVT, NULL);
 break;

 case BTM_BLE_SEC_REQ_ACT_PAIR:
      p_cb->secure_connections_only_mode_required =
 (btm_cb.security_mode == BTM_SEC_MODE_SC) ? true : false;

 /* respond to non SC pairing request as failure in SC only mode */
 if (p_cb->secure_connections_only_mode_required &&
 (auth_req & SMP_SC_SUPPORT_BIT) == 0) {
        tSMP_INT_DATA smp_int_data;
        smp_int_data.status = SMP_PAIR_AUTH_FAIL;
        smp_sm_event(p_cb, SMP_AUTH_CMPL_EVT, &smp_int_data);
 } else {
 /* initialize local i/r key to be default keys */
        p_cb->peer_auth_req = auth_req;
        p_cb->local_r_key = p_cb->local_i_key = SMP_SEC_DEFAULT_KEY;
        p_cb->cb_evt = SMP_SEC_REQUEST_EVT;
 }
 break;

 case BTM_BLE_SEC_REQ_ACT_DISCARD:
      p_cb->discard_sec_req = true;
 break;

 default:
 /* do nothing */
 break;
 }
}
