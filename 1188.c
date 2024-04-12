void    btif_dm_get_ble_local_keys(tBTA_DM_BLE_LOCAL_KEY_MASK *p_key_mask, BT_OCTET16 er,
                                   tBTA_BLE_LOCAL_ID_KEYS *p_id_keys)
{
 if (ble_local_key_cb.is_er_rcvd )
 {
        memcpy(&er[0], &ble_local_key_cb.er[0], sizeof(BT_OCTET16));
 *p_key_mask |= BTA_BLE_LOCAL_KEY_TYPE_ER;
 }

 if (ble_local_key_cb.is_id_keys_rcvd)
 {
        memcpy(&p_id_keys->ir[0], &ble_local_key_cb.id_keys.ir[0], sizeof(BT_OCTET16));
        memcpy(&p_id_keys->irk[0], &ble_local_key_cb.id_keys.irk[0], sizeof(BT_OCTET16));
        memcpy(&p_id_keys->dhk[0], &ble_local_key_cb.id_keys.dhk[0], sizeof(BT_OCTET16));
 *p_key_mask |= BTA_BLE_LOCAL_KEY_TYPE_ID;
 }
    BTIF_TRACE_DEBUG("%s  *p_key_mask=0x%02x",__FUNCTION__, *p_key_mask);
}
