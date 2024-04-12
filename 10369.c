static tBTM_SEC_SERV_REC *btm_sec_find_next_serv (tBTM_SEC_SERV_REC *p_cur)
{
    tBTM_SEC_SERV_REC *p_serv_rec   = &btm_cb.sec_serv_rec[0];
 int               i;

 for (i = 0; i < BTM_SEC_MAX_SERVICE_RECORDS; i++, p_serv_rec++)
 {
 if ((p_serv_rec->security_flags & BTM_SEC_IN_USE)
 && (p_serv_rec->psm == p_cur->psm) )
 {
 if (p_cur != p_serv_rec)
 {
 return(p_serv_rec);
 }
 }
 }
 return(NULL);
}
