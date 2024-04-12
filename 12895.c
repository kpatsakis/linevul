void smp_send_pair_fail(tSMP_CB* p_cb, tSMP_INT_DATA* p_data) {
  p_cb->status = p_data->status;
  p_cb->failure = p_data->status;

  SMP_TRACE_DEBUG("%s: status=%d failure=%d ", __func__, p_cb->status,
                  p_cb->failure);

 if (p_cb->status <= SMP_MAX_FAIL_RSN_PER_SPEC &&
      p_cb->status != SMP_SUCCESS) {
    smp_send_cmd(SMP_OPCODE_PAIRING_FAILED, p_cb);
    p_cb->wait_for_authorization_complete = true;
 }
}
