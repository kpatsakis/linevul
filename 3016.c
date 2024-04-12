static void btif_hl_proc_send_data_cfm(tBTA_HL_MDL_HANDLE mdl_handle,
                                       tBTA_HL_STATUS status){
    UINT8                   app_idx,mcl_idx, mdl_idx;
 btif_hl_mdl_cb_t *p_dcb;
    UNUSED(status);

    BTIF_TRACE_DEBUG("%s", __FUNCTION__);
 if (btif_hl_find_mdl_idx_using_handle(mdl_handle,
 &app_idx, &mcl_idx, &mdl_idx ))
 {
        p_dcb =BTIF_HL_GET_MDL_CB_PTR(app_idx, mcl_idx, mdl_idx);
        btif_hl_free_buf((void **) &p_dcb->p_tx_pkt);
        BTIF_TRACE_DEBUG("send success free p_tx_pkt tx_size=%d", p_dcb->tx_size);
        p_dcb->tx_size = 0;
 }
}
