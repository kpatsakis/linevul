BOOLEAN btif_hl_proc_pending_op(UINT8 app_idx, UINT8 mcl_idx)

{

 btif_hl_app_cb_t *p_acb = BTIF_HL_GET_APP_CB_PTR(app_idx);
 btif_hl_mcl_cb_t *p_mcb = BTIF_HL_GET_MCL_CB_PTR(app_idx, mcl_idx);
 btif_hl_pending_chan_cb_t *p_pcb;
    BOOLEAN                     status = FALSE;
    tBTA_HL_DCH_OPEN_PARAM      dch_open;
    tBTA_HL_MDL_ID              mdl_id;
    tBTA_HL_DCH_RECONNECT_PARAM reconnect_param;

    p_pcb = BTIF_HL_GET_PCB_PTR(app_idx, mcl_idx);
 if (p_pcb->in_use)
 {
 switch (p_pcb->op)
 {
 case BTIF_HL_PEND_DCH_OP_OPEN:
 if (!p_pcb->abort_pending)
 {
                    BTIF_TRACE_DEBUG("op BTIF_HL_PEND_DCH_OP_OPEN");
                    dch_open.ctrl_psm = p_mcb->ctrl_psm;
                    dch_open.local_mdep_id = p_acb->sup_feature.mdep[p_pcb->mdep_cfg_idx].mdep_id;
 if (btif_hl_find_peer_mdep_id(p_acb->app_id, p_mcb->bd_addr,
                                                  p_acb->sup_feature.mdep[p_pcb->mdep_cfg_idx].mdep_cfg.mdep_role,
                                                  p_acb->sup_feature.mdep[p_pcb->mdep_cfg_idx].mdep_cfg.data_cfg[0].data_type, &dch_open.peer_mdep_id ))
 {
                        dch_open.local_cfg = p_acb->channel_type[p_pcb->mdep_cfg_idx];
 if ((p_acb->sup_feature.mdep[p_pcb->mdep_cfg_idx].mdep_cfg.mdep_role == BTA_HL_MDEP_ROLE_SOURCE)
 && !btif_hl_is_the_first_reliable_existed(app_idx, mcl_idx))
 {
                            dch_open.local_cfg = BTA_HL_DCH_CFG_RELIABLE;
 }
                        dch_open.sec_mask = (BTA_SEC_AUTHENTICATE | BTA_SEC_ENCRYPT);
                        BTIF_TRACE_DEBUG("dch_open.local_cfg=%d  ", dch_open.local_cfg);
                        btif_hl_send_setup_connecting_cb(app_idx,mcl_idx);

 if (!btif_hl_is_reconnect_possible(app_idx, mcl_idx, p_pcb->mdep_cfg_idx, &dch_open, &mdl_id ))
 {
                            BTIF_TRACE_DEBUG("Issue DCH open, mcl_handle=%d",p_mcb->mcl_handle);
                            BTA_HlDchOpen(p_mcb->mcl_handle, &dch_open);
 }
 else
 {
                            reconnect_param.ctrl_psm = p_mcb->ctrl_psm;
                            reconnect_param.mdl_id = mdl_id;;
                            BTIF_TRACE_DEBUG("Issue Reconnect ctrl_psm=0x%x mdl_id=0x%x",reconnect_param.ctrl_psm, reconnect_param.mdl_id);
                            BTA_HlDchReconnect(p_mcb->mcl_handle, &reconnect_param);
 }
                        status = TRUE;
 }
 }
 else
 {
                    btif_hl_send_setup_disconnected_cb(app_idx, mcl_idx);
                    status = TRUE;
 }
 break;
 case BTIF_HL_PEND_DCH_OP_DELETE_MDL:
                BTA_HlDeleteMdl(p_mcb->mcl_handle, p_acb->delete_mdl.mdl_id);
                status = TRUE;
 break;

 default:
 break;
 }
 }
 return status;
}
