void bta_hl_co_get_tx_data (UINT8 app_id, tBTA_HL_MDL_HANDLE mdl_handle,
                            UINT16 buf_size, UINT8 *p_buf,  UINT16 evt)
{
    UINT8 app_idx, mcl_idx, mdl_idx;
 btif_hl_mdl_cb_t *p_dcb;
    tBTA_HL_STATUS status = BTA_HL_STATUS_FAIL;

    BTIF_TRACE_DEBUG("%s app_id=%d mdl_handle=0x%x buf_size=%d",
                      __FUNCTION__, app_id, mdl_handle, buf_size);

 if (btif_hl_find_mdl_idx_using_handle(mdl_handle, &app_idx, &mcl_idx, &mdl_idx))
 {
        p_dcb = BTIF_HL_GET_MDL_CB_PTR(app_idx, mcl_idx, mdl_idx);

 if (p_dcb->tx_size <= buf_size )
 {
            memcpy(p_buf, p_dcb->p_tx_pkt, p_dcb->tx_size);
            btif_hl_free_buf((void **) &p_dcb->p_tx_pkt);
            p_dcb->tx_size = 0;
            status = BTA_HL_STATUS_OK;
 }
 }


    bta_hl_ci_get_tx_data(mdl_handle,  status, evt);

}
