static const void* get_profile_interface (const char *profile_id)
{
    LOG_INFO("get_profile_interface %s", profile_id);

 /* sanity check */
 if (interface_ready() == FALSE)
 return NULL;

 /* check for supported profile interfaces */
 if (is_profile(profile_id, BT_PROFILE_HANDSFREE_ID))
 return btif_hf_get_interface();

 if (is_profile(profile_id, BT_PROFILE_HANDSFREE_CLIENT_ID))
 return btif_hf_client_get_interface();

 if (is_profile(profile_id, BT_PROFILE_SOCKETS_ID))
 return btif_sock_get_interface();

 if (is_profile(profile_id, BT_PROFILE_PAN_ID))
 return btif_pan_get_interface();

 if (is_profile(profile_id, BT_PROFILE_ADVANCED_AUDIO_ID))
 return btif_av_get_src_interface();

 if (is_profile(profile_id, BT_PROFILE_ADVANCED_AUDIO_SINK_ID))
 return btif_av_get_sink_interface();

 if (is_profile(profile_id, BT_PROFILE_HIDHOST_ID))
 return btif_hh_get_interface();

 if (is_profile(profile_id, BT_PROFILE_HEALTH_ID))
 return btif_hl_get_interface();

 if (is_profile(profile_id, BT_PROFILE_SDP_CLIENT_ID))
 return btif_sdp_get_interface();

#if ( BTA_GATT_INCLUDED == TRUE && BLE_INCLUDED == TRUE)
 if (is_profile(profile_id, BT_PROFILE_GATT_ID))
 return btif_gatt_get_interface();
#endif

 if (is_profile(profile_id, BT_PROFILE_AV_RC_ID))
 return btif_rc_get_interface();

 if (is_profile(profile_id, BT_PROFILE_AV_RC_CTRL_ID))
 return btif_rc_ctrl_get_interface();

 return NULL;
}
