static void btsock_l2cap_cbk(tBTA_JV_EVT event, tBTA_JV *p_data, void *user_data)
{
 int rc;

 switch (event) {
 case BTA_JV_L2CAP_START_EVT:
        on_srv_l2cap_listen_started(&p_data->l2c_start, (uint32_t)user_data);
 break;

 case BTA_JV_L2CAP_CL_INIT_EVT:
        on_cl_l2cap_init(&p_data->l2c_cl_init, (uint32_t)user_data);
 break;

 case BTA_JV_L2CAP_OPEN_EVT:
        on_l2cap_connect(p_data, (uint32_t)user_data);
        BTA_JvSetPmProfile(p_data->l2c_open.handle,BTA_JV_PM_ID_1,BTA_JV_CONN_OPEN);
 break;

 case BTA_JV_L2CAP_CLOSE_EVT:
        APPL_TRACE_DEBUG("BTA_JV_L2CAP_CLOSE_EVT: user_data:%d", (uint32_t)user_data);
        on_l2cap_close(&p_data->l2c_close, (uint32_t)user_data);
 break;

 case BTA_JV_L2CAP_DATA_IND_EVT:
        on_l2cap_data_ind(p_data, (uint32_t)user_data);
        APPL_TRACE_DEBUG("BTA_JV_L2CAP_DATA_IND_EVT");
 break;

 case BTA_JV_L2CAP_READ_EVT:
        APPL_TRACE_DEBUG("BTA_JV_L2CAP_READ_EVT not used");
 break;

 case BTA_JV_L2CAP_RECEIVE_EVT:
        APPL_TRACE_DEBUG("BTA_JV_L2CAP_RECEIVE_EVT not used");
 break;

 case BTA_JV_L2CAP_WRITE_EVT:
        APPL_TRACE_DEBUG("BTA_JV_L2CAP_WRITE_EVT id: %d", (int)user_data);
        on_l2cap_write_done((void*)p_data->l2c_write.req_id, (uint32_t)user_data);
 break;

 case BTA_JV_L2CAP_WRITE_FIXED_EVT:
        APPL_TRACE_DEBUG("BTA_JV_L2CAP_WRITE_FIXED_EVT id: %d", (int)user_data);
        on_l2cap_write_fixed_done((void*)p_data->l2c_write_fixed.req_id, (uint32_t)user_data);
 break;

 case BTA_JV_L2CAP_CONG_EVT:
        on_l2cap_outgoing_congest(&p_data->l2c_cong, (uint32_t)user_data);
 break;

 default:
        APPL_TRACE_ERROR("unhandled event %d, slot id:%d", event, (uint32_t)user_data);
 break;
 }
}
