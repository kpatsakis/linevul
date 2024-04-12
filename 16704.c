static void  cleanup( void )
{
    BTIF_TRACE_EVENT("%s", __FUNCTION__);
 btif_hh_device_t *p_dev;
 int i;
 if (btif_hh_cb.status == BTIF_HH_DISABLED) {
        BTIF_TRACE_WARNING("%s: HH disabling or disabled already, status = %d", __FUNCTION__, btif_hh_cb.status);
 return;
 }
    btif_hh_cb.status = BTIF_HH_DISABLING;
 for (i = 0; i < BTIF_HH_MAX_HID; i++) {
         p_dev = &btif_hh_cb.devices[i];
 if (p_dev->dev_status != BTHH_CONN_STATE_UNKNOWN && p_dev->fd >= 0) {
             BTIF_TRACE_DEBUG("%s: Closing uhid fd = %d", __FUNCTION__, p_dev->fd);
 if (p_dev->fd >= 0) {
                 bta_hh_co_destroy(p_dev->fd);
                 p_dev->fd = -1;
 }
             p_dev->hh_keep_polling = 0;
             p_dev->hh_poll_thread_id = -1;
 }
 }

 if (bt_hh_callbacks)
 {
        btif_disable_service(BTA_HID_SERVICE_ID);
        bt_hh_callbacks = NULL;
 }

}
