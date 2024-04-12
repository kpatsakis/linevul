static btif_hh_device_t *btif_hh_find_dev_by_bda(bt_bdaddr_t *bd_addr)
{
    UINT32 i;
 for (i = 0; i < BTIF_HH_MAX_HID; i++) {
 if (btif_hh_cb.devices[i].dev_status != BTHH_CONN_STATE_UNKNOWN &&
            memcmp(&(btif_hh_cb.devices[i].bd_addr), bd_addr, BD_ADDR_LEN) == 0)
 {
 return &btif_hh_cb.devices[i];
 }
 }
 return NULL;
}
