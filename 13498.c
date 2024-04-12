OMX_ERRORTYPE  omx_video::empty_this_buffer_opaque(OMX_IN OMX_HANDLETYPE hComp,
        OMX_IN OMX_BUFFERHEADERTYPE* buffer)
{
 unsigned nBufIndex = 0;
    OMX_ERRORTYPE ret = OMX_ErrorNone;
    encoder_media_buffer_type *media_buffer;
 private_handle_t *handle = NULL;
    DEBUG_PRINT_LOW("ETBProxyOpaque: buffer[%p]", buffer);

 if (buffer == NULL) {
        DEBUG_PRINT_ERROR("ERROR: ETBProxyA: Invalid buffer[%p]",buffer);
 return OMX_ErrorBadParameter;
 }
    nBufIndex = buffer - meta_buffer_hdr;
 if (nBufIndex >= m_sInPortDef.nBufferCountActual) {
        DEBUG_PRINT_ERROR("ERROR: ETBProxyA: Invalid bufindex = %u",
                nBufIndex);
 return OMX_ErrorBadParameter;
 }
    media_buffer = (encoder_media_buffer_type *)buffer->pBuffer;
 if ((!media_buffer || !media_buffer->meta_handle) &&
 !(buffer->nFlags & OMX_BUFFERFLAG_EOS)) {
        DEBUG_PRINT_ERROR("Incorrect Buffer queued media buffer = %p",
            media_buffer);
        m_pCallbacks.EmptyBufferDone(hComp, m_app_data, buffer);
 return OMX_ErrorBadParameter;
 } else if (media_buffer) {
        handle = (private_handle_t *)media_buffer->meta_handle;
 }

 if (buffer->nFilledLen > 0 && handle) {
 /*Enable following code once private handle color format is
            updated correctly*/
 if (handle->format == HAL_PIXEL_FORMAT_RGBA_8888)
            mUsesColorConversion = true;
 else
            mUsesColorConversion = false;

 if (c2d_opened && handle->format != c2d_conv.get_src_format()) {
            c2d_conv.close();
            c2d_opened = false;
 }
 if (!c2d_opened) {
 if (handle->format == HAL_PIXEL_FORMAT_RGBA_8888) {
                DEBUG_PRINT_INFO("open Color conv for RGBA888 W: %u, H: %u",
 (unsigned int)m_sInPortDef.format.video.nFrameWidth,
 (unsigned int)m_sInPortDef.format.video.nFrameHeight);
 if (!c2d_conv.open(m_sInPortDef.format.video.nFrameHeight,
                            m_sInPortDef.format.video.nFrameWidth,
                            RGBA8888, NV12_128m, handle->width)) {
                    m_pCallbacks.EmptyBufferDone(hComp,m_app_data,buffer);
                    DEBUG_PRINT_ERROR("Color conv open failed");
 return OMX_ErrorBadParameter;
 }
                c2d_opened = true;
#ifdef _MSM8974_
 if (!dev_set_format(handle->format))
                    DEBUG_PRINT_ERROR("cannot set color format for RGBA8888");
#endif
 } else if (handle->format != HAL_PIXEL_FORMAT_NV12_ENCODEABLE &&
                    handle->format != QOMX_COLOR_FORMATYUV420PackedSemiPlanar32m &&
                    handle->format != QOMX_COLOR_FormatYVU420SemiPlanar) {
                DEBUG_PRINT_ERROR("Incorrect color format");
                m_pCallbacks.EmptyBufferDone(hComp,m_app_data,buffer);
 return OMX_ErrorBadParameter;
 }
 }
 }
 if (input_flush_progress == true) {
        m_pCallbacks.EmptyBufferDone(hComp,m_app_data,buffer);
        DEBUG_PRINT_ERROR("ERROR: ETBProxyA: Input flush in progress");
 return OMX_ErrorNone;
 }

 if (!psource_frame) {
        psource_frame = buffer;
        ret = push_input_buffer(hComp);
 } else {
 if (!m_opq_meta_q.insert_entry((unsigned long)buffer,0,0)) {
            DEBUG_PRINT_ERROR("ERROR: ETBProxy: Queue is full");
            m_pCallbacks.EmptyBufferDone(hComp,m_app_data,buffer);
            ret = OMX_ErrorBadParameter;
 }
 }
 return ret;
}
