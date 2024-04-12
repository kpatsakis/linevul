static void bta_pan_callback_transfer(UINT16 event, char *p_param)
{
    tBTA_PAN *p_data = (tBTA_PAN *)p_param;

 switch(event)
 {
 case BTA_PAN_ENABLE_EVT:
            BTIF_TRACE_DEBUG("BTA_PAN_ENABLE_EVT");
 break;
 case BTA_PAN_SET_ROLE_EVT:
 {
 int btpan_role = bta_role_to_btpan(p_data->set_role.role);
 bt_status_t status = p_data->set_role.status == BTA_PAN_SUCCESS ? BT_STATUS_SUCCESS : BT_STATUS_FAIL;
 btpan_control_state_t state = btpan_role == 0 ? BTPAN_STATE_DISABLED : BTPAN_STATE_ENABLED;
                callback.control_state_cb(state, btpan_role, status, TAP_IF_NAME);
 break;
 }
 case BTA_PAN_OPENING_EVT:
 {
 btpan_conn_t* conn;
 bdstr_t bds;
                bdaddr_to_string((bt_bdaddr_t *)p_data->opening.bd_addr, bds, sizeof(bds));
                BTIF_TRACE_DEBUG("BTA_PAN_OPENING_EVT handle %d, addr: %s", p_data->opening.handle, bds);
                conn = btpan_find_conn_addr(p_data->opening.bd_addr);

                asrt(conn != NULL);
 if (conn)
 {
                    conn->handle = p_data->opening.handle;
 int btpan_conn_local_role = bta_role_to_btpan(conn->local_role);
 int btpan_remote_role = bta_role_to_btpan(conn->remote_role);
                    callback.connection_state_cb(BTPAN_STATE_CONNECTING, BT_STATUS_SUCCESS,
 (const bt_bdaddr_t*)p_data->opening.bd_addr, btpan_conn_local_role, btpan_remote_role);
 }
 else
                    BTIF_TRACE_ERROR("connection not found");
 break;
 }
 case BTA_PAN_OPEN_EVT:
 {
 btpan_connection_state_t state;
 bt_status_t status;
 btpan_conn_t *conn = btpan_find_conn_handle(p_data->open.handle);

                LOG_VERBOSE("%s pan connection open status: %d", __func__, p_data->open.status);
 if (p_data->open.status == BTA_PAN_SUCCESS)
 {
                    state = BTPAN_STATE_CONNECTED;
                    status = BT_STATUS_SUCCESS;
                    btpan_open_conn(conn, p_data);
 }
 else
 {
                    state = BTPAN_STATE_DISCONNECTED;
                    status = BT_STATUS_FAIL;
                    btpan_cleanup_conn(conn);
 }
 /* debug("BTA_PAN_OPEN_EVT handle:%d, conn:%p",  p_data->open.handle, conn); */
 /* debug("conn bta local_role:%d, bta remote role:%d", conn->local_role, conn->remote_role); */
 int btpan_conn_local_role = bta_role_to_btpan(p_data->open.local_role);
 int btpan_remote_role = bta_role_to_btpan(p_data->open.peer_role);
                callback.connection_state_cb(state, status, (const bt_bdaddr_t*)p_data->open.bd_addr,
                        btpan_conn_local_role, btpan_remote_role);
 break;
 }
 case BTA_PAN_CLOSE_EVT:
 {
 btpan_conn_t* conn = btpan_find_conn_handle(p_data->close.handle);

                LOG_INFO("%s: event = BTA_PAN_CLOSE_EVT handle %d", __FUNCTION__, p_data->close.handle);
                btpan_close_conn(conn);

 if (conn && conn->handle >= 0)
 {
 int btpan_conn_local_role = bta_role_to_btpan(conn->local_role);
 int btpan_remote_role = bta_role_to_btpan(conn->remote_role);
                    callback.connection_state_cb(BTPAN_STATE_DISCONNECTED, 0, (const bt_bdaddr_t*)conn->peer,
                            btpan_conn_local_role, btpan_remote_role);
                    btpan_cleanup_conn(conn);
 }
 else
                    BTIF_TRACE_ERROR("pan handle not found (%d)", p_data->close.handle);
 break;
 }
 default:
            BTIF_TRACE_WARNING("Unknown pan event %d", event);
 break;
 }
}
