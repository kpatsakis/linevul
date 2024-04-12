static tAVRC_STS bta_av_chk_notif_evt_id(tAVRC_MSG_VENDOR* p_vendor) {
  tAVRC_STS status = BTA_AV_STS_NO_RSP;
 uint8_t xx;
 uint16_t u16;
 uint8_t* p = p_vendor->p_vendor_data + 2;

  BE_STREAM_TO_UINT16(u16, p);
 /* double check the fixed length */
 if ((u16 != 5) || (p_vendor->vendor_len != 9)) {
    status = AVRC_STS_INTERNAL_ERR;
 } else {
 /* make sure the player_id is valid */
 for (xx = 0; xx < p_bta_av_cfg->num_evt_ids; xx++) {
 if (*p == p_bta_av_cfg->p_meta_evt_ids[xx]) {
 break;
 }
 }
 if (xx == p_bta_av_cfg->num_evt_ids) {
      status = AVRC_STS_BAD_PARAM;
 }
 }

 return status;
}
