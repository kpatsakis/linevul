static BOOLEAN btm_serv_trusted(tBTM_SEC_DEV_REC *p_dev_rec, tBTM_SEC_SERV_REC *p_serv_rec)
{
 if(BTM_SEC_IS_SERVICE_TRUSTED(p_dev_rec->trusted_mask, p_serv_rec->service_id))
 {
 return(TRUE);
 }
 return(FALSE);
}
