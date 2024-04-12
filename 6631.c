void bta_av_del_rc(tBTA_AV_RCB* p_rcb) {
  tBTA_AV_SCB* p_scb;
 uint8_t rc_handle; /* connected AVRCP handle */

  p_scb = NULL;
 if (p_rcb->handle != BTA_AV_RC_HANDLE_NONE) {
 if (p_rcb->shdl) {
 /* Validate array index*/
 if ((p_rcb->shdl - 1) < BTA_AV_NUM_STRS) {
        p_scb = bta_av_cb.p_scb[p_rcb->shdl - 1];
 }
 if (p_scb) {
        APPL_TRACE_DEBUG("%s: shdl:%d, srch:%d rc_handle:%d", __func__,
                         p_rcb->shdl, p_scb->rc_handle, p_rcb->handle);
 if (p_scb->rc_handle == p_rcb->handle)
          p_scb->rc_handle = BTA_AV_RC_HANDLE_NONE;
 /* just in case the RC timer is active
        if (bta_av_cb.features & BTA_AV_FEAT_RCCT && p_scb->chnl ==
        BTA_AV_CHNL_AUDIO) */
        alarm_cancel(p_scb->avrc_ct_timer);
 }
 }

    APPL_TRACE_EVENT("%s: handle: %d status=0x%x, rc_acp_handle:%d, idx:%d",
                     __func__, p_rcb->handle, p_rcb->status,
                     bta_av_cb.rc_acp_handle, bta_av_cb.rc_acp_idx);
    rc_handle = p_rcb->handle;
 if (!(p_rcb->status & BTA_AV_RC_CONN_MASK) ||
 ((p_rcb->status & BTA_AV_RC_ROLE_MASK) == BTA_AV_RC_ROLE_INT)) {
      p_rcb->status = 0;
      p_rcb->handle = BTA_AV_RC_HANDLE_NONE;
      p_rcb->shdl = 0;
      p_rcb->lidx = 0;
 }
 /* else ACP && connected. do not clear the handle yet */
    AVRC_Close(rc_handle);
 if (rc_handle == bta_av_cb.rc_acp_handle)
      bta_av_cb.rc_acp_handle = BTA_AV_RC_HANDLE_NONE;
    APPL_TRACE_EVENT(
 "%s: end del_rc handle: %d status=0x%x, rc_acp_handle:%d, lidx:%d",
        __func__, p_rcb->handle, p_rcb->status, bta_av_cb.rc_acp_handle,
        p_rcb->lidx);
 }
}
