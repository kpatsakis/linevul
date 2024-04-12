void BTM_SendKeypressNotif(BD_ADDR bd_addr, tBTM_SP_KEY_TYPE type)
{
 /* This API only make sense between PASSKEY_REQ and SP complete */
 if (btm_cb.pairing_state == BTM_PAIR_STATE_KEY_ENTRY)
        btsnd_hcic_send_keypress_notif (bd_addr, type);
}
