void smp_send_pair_rsp(tSMP_CB* p_cb, tSMP_INT_DATA* p_data) {
  SMP_TRACE_DEBUG("%s", __func__);

  p_cb->local_i_key &= p_cb->peer_i_key;
  p_cb->local_r_key &= p_cb->peer_r_key;

 if (smp_send_cmd(SMP_OPCODE_PAIRING_RSP, p_cb)) {
 if (p_cb->selected_association_model == SMP_MODEL_SEC_CONN_OOB)
      smp_use_oob_private_key(p_cb, NULL);
 else
      smp_decide_association_model(p_cb, NULL);
 }
}
