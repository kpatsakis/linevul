OMX_ERRORTYPE omx_vdec::is_video_session_supported()
{
 if (!strncmp(drv_ctx.kind, "OMX.qcom.video.decoder.avc",
                OMX_MAX_STRINGNAME_SIZE) &&
 (m_profile == HIGH_PROFILE || m_profile == MAIN_PROFILE)) {
        m_decoder_capability.max_width = 1280;
        m_decoder_capability.max_height = 720;
        DEBUG_PRINT_HIGH("Set max_width=1280 & max_height=720 for H264 HP/MP");
 }

 if ((drv_ctx.video_resolution.frame_width *
                drv_ctx.video_resolution.frame_height >
                m_decoder_capability.max_width *
                m_decoder_capability.max_height) ||
 (drv_ctx.video_resolution.frame_width*
             drv_ctx.video_resolution.frame_height <
             m_decoder_capability.min_width *
             m_decoder_capability.min_height)) {
        DEBUG_PRINT_ERROR(
 "Unsupported WxH = (%u)x(%u) supported range is min(%u)x(%u) - max(%u)x(%u)",
                drv_ctx.video_resolution.frame_width,
                drv_ctx.video_resolution.frame_height,
                m_decoder_capability.min_width,
                m_decoder_capability.min_height,
                m_decoder_capability.max_width,
                m_decoder_capability.max_height);
 return OMX_ErrorUnsupportedSetting;
 }
    DEBUG_PRINT_HIGH("video session supported");
 return OMX_ErrorNone;
}
