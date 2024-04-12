static void btif_hl_proc_dch_close_cfm(tBTA_HL *p_data)

{
 btif_hl_mdl_cb_t *p_dcb;
 btif_hl_mcl_cb_t *p_mcb;
    UINT8                   app_idx, mcl_idx, mdl_idx;

    BTIF_TRACE_DEBUG("%s", __FUNCTION__);
 if (btif_hl_find_mdl_idx_using_handle(p_data->dch_close_cfm.mdl_handle,
 &app_idx, &mcl_idx, &mdl_idx ))
 {
        p_dcb = BTIF_HL_GET_MDL_CB_PTR(app_idx, mcl_idx, mdl_idx);
        btif_hl_release_socket(app_idx,mcl_idx,mdl_idx);
        btif_hl_clean_mdl_cb(p_dcb);
        p_mcb =  BTIF_HL_GET_MCL_CB_PTR(app_idx,mcl_idx);
 if (!btif_hl_num_dchs_in_use(p_mcb->mcl_handle))
            btif_hl_start_cch_timer(app_idx, mcl_idx);
        BTIF_TRACE_DEBUG(" local DCH close success mdl_idx=%d", mdl_idx);
 }
}
