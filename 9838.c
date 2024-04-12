void btif_hl_release_socket(UINT8 app_idx, UINT8 mcl_idx, UINT8 mdl_idx){
 btif_hl_soc_cb_t *p_scb = NULL;
 btif_hl_mdl_cb_t *p_dcb = BTIF_HL_GET_MDL_CB_PTR(app_idx, mcl_idx, mdl_idx);

    BTIF_TRACE_DEBUG("%s", __FUNCTION__);
    BTIF_TRACE_DEBUG("app_idx=%d mcl_idx=%d mdl_idx=%d",  app_idx, mcl_idx, mdl_idx  );

 if (p_dcb && p_dcb->p_scb)
 {
        p_scb = p_dcb->p_scb;
        btif_hl_set_socket_state(p_scb,  BTIF_HL_SOC_STATE_W4_REL);
        p_dcb->p_scb = NULL;
        btif_hl_select_close_connected();
 }
}
