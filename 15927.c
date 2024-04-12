BOOLEAN btm_sec_is_a_bonded_dev (BD_ADDR bda)
{

    tBTM_SEC_DEV_REC *p_dev_rec= btm_find_dev (bda);
    BOOLEAN is_bonded= FALSE;

 if (p_dev_rec &&
#if (SMP_INCLUDED== TRUE)
 ((p_dev_rec->ble.key_type && (p_dev_rec->sec_flags & BTM_SEC_LE_LINK_KEY_KNOWN))||
#endif
 (p_dev_rec->sec_flags & BTM_SEC_LINK_KEY_KNOWN)))
 {
        is_bonded = TRUE;
 }
    BTM_TRACE_DEBUG ("btm_sec_is_a_bonded_dev is_bonded=%d", is_bonded);
 return(is_bonded);
}
