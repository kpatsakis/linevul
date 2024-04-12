bt_status_t btif_hh_connect(bt_bdaddr_t *bd_addr)
{
 btif_hh_device_t *dev;
 btif_hh_added_device_t *added_dev = NULL;
 char bda_str[20];
 int i;
    BD_ADDR *bda = (BD_ADDR*)bd_addr;
    CHECK_BTHH_INIT();
    dev = btif_hh_find_dev_by_bda(bd_addr);
    BTIF_TRACE_DEBUG("Connect _hh");
    sprintf(bda_str, "%02X:%02X:%02X:%02X:%02X:%02X",
 (*bda)[0], (*bda)[1], (*bda)[2], (*bda)[3], (*bda)[4], (*bda)[5]);
 if (dev == NULL && btif_hh_cb.device_num >= BTIF_HH_MAX_HID) {
         BTIF_TRACE_WARNING("%s: Error, exceeded the maximum supported HID device number %d",
             __FUNCTION__, BTIF_HH_MAX_HID);
 return BT_STATUS_FAIL;
 }

 for (i = 0; i < BTIF_HH_MAX_ADDED_DEV; i++) {
 if (memcmp(&(btif_hh_cb.added_devices[i].bd_addr), bd_addr, BD_ADDR_LEN) == 0) {
            added_dev = &btif_hh_cb.added_devices[i];
             BTIF_TRACE_WARNING("%s: Device %s already added, attr_mask = 0x%x",
                 __FUNCTION__, bda_str, added_dev->attr_mask);
 }
 }

 if (added_dev != NULL) {
 if (added_dev->dev_handle == BTA_HH_INVALID_HANDLE) {
            BTIF_TRACE_ERROR("%s: Error, device %s added but addition failed", __FUNCTION__, bda_str);
            memset(&(added_dev->bd_addr), 0, 6);
            added_dev->dev_handle = BTA_HH_INVALID_HANDLE;
 return BT_STATUS_FAIL;
 }
 }

 /* Not checking the NORMALLY_Connectible flags from sdp record, and anyways sending this
     request from host, for subsequent user initiated connection. If the remote is not in
     pagescan mode, we will do 2 retries to connect before giving up */
    tBTA_SEC sec_mask = BTUI_HH_SECURITY;
    btif_hh_cb.status = BTIF_HH_DEV_CONNECTING;
    BTA_HhOpen(*bda, BTA_HH_PROTO_RPT_MODE, sec_mask);

    HAL_CBACK(bt_hh_callbacks, connection_state_cb, bd_addr, BTHH_CONN_STATE_CONNECTING);
 return BT_STATUS_SUCCESS;
}
