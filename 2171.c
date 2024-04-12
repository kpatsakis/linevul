void BTM_PasskeyReqReply(tBTM_STATUS res, BD_ADDR bd_addr, UINT32 passkey)
{
    tBTM_SEC_DEV_REC *p_dev_rec;

    BTM_TRACE_API ("BTM_PasskeyReqReply: State: %s  res:%d",
                    btm_pair_state_descr(btm_cb.pairing_state), res);

 if ( (btm_cb.pairing_state == BTM_PAIR_STATE_IDLE)
 || (memcmp (btm_cb.pairing_bda, bd_addr, BD_ADDR_LEN) != 0) )
 {
 return;
 }

 /* If timeout already expired or has been canceled, ignore the reply */
 if ( (btm_cb.pairing_state == BTM_PAIR_STATE_WAIT_AUTH_COMPLETE) && (res != BTM_SUCCESS) )
 {
 if ((p_dev_rec = btm_find_dev (bd_addr)) != NULL)
 {
            btm_cb.acl_disc_reason = HCI_ERR_HOST_REJECT_SECURITY;

 if (p_dev_rec->hci_handle != BTM_SEC_INVALID_HANDLE)
                btm_sec_send_hci_disconnect (p_dev_rec, HCI_ERR_AUTH_FAILURE, p_dev_rec->hci_handle);
 else
                BTM_SecBondCancel(bd_addr);

            p_dev_rec->sec_flags &= ~(BTM_SEC_LINK_KEY_AUTHED | BTM_SEC_LINK_KEY_KNOWN);

            btm_sec_change_pairing_state (BTM_PAIR_STATE_IDLE);
 return;
 }
 }
 else if (btm_cb.pairing_state != BTM_PAIR_STATE_KEY_ENTRY)
 return;

 if (passkey > BTM_MAX_PASSKEY_VAL)
        res = BTM_ILLEGAL_VALUE;

    btm_sec_change_pairing_state (BTM_PAIR_STATE_WAIT_AUTH_COMPLETE);

 if (res != BTM_SUCCESS)
 {
 /* use BTM_PAIR_STATE_WAIT_AUTH_COMPLETE to report authentication failed event */
        btm_cb.acl_disc_reason = HCI_ERR_HOST_REJECT_SECURITY;
        btsnd_hcic_user_passkey_neg_reply (bd_addr);
 }
 else
 {
        btm_cb.acl_disc_reason = HCI_SUCCESS;
        btsnd_hcic_user_passkey_reply (bd_addr, passkey);
 }
}
