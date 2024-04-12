void rfc_send_msc(tRFC_MCB* p_mcb, uint8_t dlci, bool is_command,
                  tPORT_CTRL* p_pars) {
 uint8_t* p_data;
 uint8_t signals;
 uint8_t break_duration;
 uint8_t len;
  BT_HDR* p_buf = (BT_HDR*)osi_malloc(RFCOMM_CMD_BUF_SIZE);

  signals = p_pars->modem_signal;
  break_duration = p_pars->break_signal;

  p_buf->offset = L2CAP_MIN_OFFSET + RFCOMM_CTRL_FRAME_LEN;
  p_data = (uint8_t*)(p_buf + 1) + p_buf->offset;

 if (break_duration)
    len = RFCOMM_MX_MSC_LEN_WITH_BREAK;
 else
    len = RFCOMM_MX_MSC_LEN_NO_BREAK;

 *p_data++ = RFCOMM_EA | RFCOMM_I_CR(is_command) | RFCOMM_MX_MSC;
 *p_data++ = RFCOMM_EA | (len << 1);

 *p_data++ = RFCOMM_EA | RFCOMM_CR_MASK | (dlci << RFCOMM_SHIFT_DLCI);
 *p_data++ = RFCOMM_EA | ((p_pars->fc) ? RFCOMM_MSC_FC : 0) |
 ((signals & MODEM_SIGNAL_DTRDSR) ? RFCOMM_MSC_RTC : 0) |
 ((signals & MODEM_SIGNAL_RTSCTS) ? RFCOMM_MSC_RTR : 0) |
 ((signals & MODEM_SIGNAL_RI) ? RFCOMM_MSC_IC : 0) |
 ((signals & MODEM_SIGNAL_DCD) ? RFCOMM_MSC_DV : 0);

 if (break_duration) {
 *p_data++ = RFCOMM_EA | RFCOMM_MSC_BREAK_PRESENT_MASK |
 (break_duration << RFCOMM_MSC_SHIFT_BREAK);
 }

 /* Total length is sizeof MSC data + mx header 2 */
  p_buf->len = len + 2;

  rfc_send_buf_uih(p_mcb, RFCOMM_MX_DLCI, p_buf);
}
