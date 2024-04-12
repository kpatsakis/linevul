BOOLEAN btif_hl_find_app_idx_using_deleted_mdl_id( UINT8 mdl_id,
                                           UINT8 *p_app_idx){
 btif_hl_app_cb_t *p_acb;
    BOOLEAN         found=FALSE;
    UINT8 i;

 for (i=0; i<BTA_HL_NUM_APPS; i++)
 {
        p_acb =BTIF_HL_GET_APP_CB_PTR(i);
 if (p_acb->delete_mdl.active) {
            BTIF_TRACE_DEBUG("%s: app_idx=%d, mdl_id=%d",
                             __FUNCTION__,i,mdl_id);
 }
 if (p_acb->delete_mdl.active &&
 (p_acb->delete_mdl.mdl_id == mdl_id))
 {
            found = TRUE;
 *p_app_idx = i;
 break;
 }
 }
    BTIF_TRACE_DEBUG("%s found=%d app_idx=%d",__FUNCTION__,
                      found, i);
 return found;
}
