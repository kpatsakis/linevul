static bt_status_t init_src(
 btav_source_callbacks_t* callbacks,
    std::vector<btav_a2dp_codec_config_t> codec_priorities) {
  BTIF_TRACE_EVENT("%s", __func__);

  btif_av_cb.codec_priorities = codec_priorities;
 bt_status_t status = btif_av_init(BTA_A2DP_SOURCE_SERVICE_ID);
 if (status == BT_STATUS_SUCCESS) bt_av_src_callbacks = callbacks;

 return status;
}
