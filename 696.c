static void *rfcomm_cback(tBTA_JV_EVT event, tBTA_JV *p_data, void *user_data) {
 void *new_user_data = NULL;

 switch (event) {
 case BTA_JV_RFCOMM_START_EVT:
      on_srv_rfc_listen_started(&p_data->rfc_start, (uintptr_t)user_data);
 break;

 case BTA_JV_RFCOMM_CL_INIT_EVT:
      on_cl_rfc_init(&p_data->rfc_cl_init, (uintptr_t)user_data);
 break;

 case BTA_JV_RFCOMM_OPEN_EVT:
      BTA_JvSetPmProfile(p_data->rfc_open.handle,BTA_JV_PM_ID_1,BTA_JV_CONN_OPEN);
      on_cli_rfc_connect(&p_data->rfc_open, (uintptr_t)user_data);
 break;

 case BTA_JV_RFCOMM_SRV_OPEN_EVT:
      BTA_JvSetPmProfile(p_data->rfc_srv_open.handle,BTA_JV_PM_ALL,BTA_JV_CONN_OPEN);
      new_user_data = (void *)(uintptr_t)on_srv_rfc_connect(&p_data->rfc_srv_open, (uintptr_t)user_data);
 break;

 case BTA_JV_RFCOMM_CLOSE_EVT:
      APPL_TRACE_DEBUG("BTA_JV_RFCOMM_CLOSE_EVT: user_data:%d", (uintptr_t)user_data);
      on_rfc_close(&p_data->rfc_close, (uintptr_t)user_data);
 break;

 case BTA_JV_RFCOMM_WRITE_EVT:
      on_rfc_write_done(&p_data->rfc_write, (uintptr_t)user_data);
 break;

 case BTA_JV_RFCOMM_CONG_EVT:
      on_rfc_outgoing_congest(&p_data->rfc_cong, (uintptr_t)user_data);
 break;

 case BTA_JV_RFCOMM_READ_EVT:
 case BTA_JV_RFCOMM_DATA_IND_EVT:
 break;

 default:
      LOG_ERROR("%s unhandled event %d, slot id: %zi", __func__, event, (uintptr_t)user_data);
 break;
 }
 return new_user_data;
}
