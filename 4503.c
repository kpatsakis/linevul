void handle_rc_features()
{
 btrc_remote_features_t rc_features = BTRC_FEAT_NONE;
 bt_bdaddr_t rc_addr;
    bdcpy(rc_addr.address, btif_rc_cb.rc_addr);


 if (btif_rc_cb.rc_features & BTA_AV_FEAT_BROWSE)
 {
        rc_features |= BTRC_FEAT_BROWSE;
 }

 if ( (btif_rc_cb.rc_features & BTA_AV_FEAT_ADV_CTRL) &&
 (btif_rc_cb.rc_features & BTA_AV_FEAT_RCTG))
 {
        rc_features |= BTRC_FEAT_ABSOLUTE_VOLUME;
 }

 if (btif_rc_cb.rc_features & BTA_AV_FEAT_METADATA)
 {
        rc_features |= BTRC_FEAT_METADATA;
 }

    BTIF_TRACE_DEBUG("%s: rc_features=0x%x", __FUNCTION__, rc_features);
    HAL_CBACK(bt_rc_callbacks, remote_features_cb, &rc_addr, rc_features)

#if (AVRC_ADV_CTRL_INCLUDED == TRUE)
     BTIF_TRACE_DEBUG("Checking for feature flags in btif_rc_handler with label %d",
                        btif_rc_cb.rc_vol_label);
 if(btif_rc_cb.rc_features & BTA_AV_FEAT_ADV_CTRL &&
         btif_rc_cb.rc_features & BTA_AV_FEAT_RCTG)
 {
 rc_transaction_t *p_transaction=NULL;
 bt_status_t status = BT_STATUS_NOT_READY;
 if(MAX_LABEL==btif_rc_cb.rc_vol_label)
 {
            status=get_transaction(&p_transaction);
 }
 else
 {
            p_transaction=get_transaction_by_lbl(btif_rc_cb.rc_vol_label);
 if(NULL!=p_transaction)
 {
               BTIF_TRACE_DEBUG("register_volumechange already in progress for label %d",
                                  btif_rc_cb.rc_vol_label);
 return;
 }
 else
              status=get_transaction(&p_transaction);
 }

 if(BT_STATUS_SUCCESS == status && NULL!=p_transaction)
 {
            btif_rc_cb.rc_vol_label=p_transaction->lbl;
            register_volumechange(btif_rc_cb.rc_vol_label);
 }
 }
#endif
}
