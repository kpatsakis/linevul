static BOOLEAN btm_sec_start_get_name (tBTM_SEC_DEV_REC *p_dev_rec)
{
    UINT8 tempstate = p_dev_rec->sec_state;

    p_dev_rec->sec_state = BTM_SEC_STATE_GETTING_NAME;

 /* Device should be connected, no need to provide correct page params */
 /* 0 and NULL are as timeout and callback params because they are not used in security get name case */
 if ((btm_initiate_rem_name (p_dev_rec->bd_addr, NULL, BTM_RMT_NAME_SEC,
 0, NULL)) != BTM_CMD_STARTED)
 {
        p_dev_rec->sec_state = tempstate;
 return(FALSE);
 }

 return(TRUE);
}
