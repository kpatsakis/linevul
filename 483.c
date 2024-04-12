OMX_ERRORTYPE omx_vdec::use_android_native_buffer(OMX_IN OMX_HANDLETYPE hComp, OMX_PTR data)
{
    DEBUG_PRINT_LOW("Inside use_android_native_buffer");
    OMX_ERRORTYPE eRet = OMX_ErrorNone;
 UseAndroidNativeBufferParams *params = (UseAndroidNativeBufferParams *)data;

 if ((params == NULL) ||
 (params->nativeBuffer == NULL) ||
 (params->nativeBuffer->handle == NULL) ||
 !m_enable_android_native_buffers)
 return OMX_ErrorBadParameter;
    m_use_android_native_buffers = OMX_TRUE;
    sp<android_native_buffer_t> nBuf = params->nativeBuffer;
 private_handle_t *handle = (private_handle_t *)nBuf->handle;
 if (OMX_CORE_OUTPUT_PORT_INDEX == params->nPortIndex) { //android native buffers can be used only on Output port
        OMX_U8 *buffer = NULL;
 if (!secure_mode) {
            buffer = (OMX_U8*)mmap(0, handle->size,
                    PROT_READ|PROT_WRITE, MAP_SHARED, handle->fd, 0);
 if (buffer == MAP_FAILED) {
                DEBUG_PRINT_ERROR("Failed to mmap pmem with fd = %d, size = %d", handle->fd, handle->size);
 return OMX_ErrorInsufficientResources;
 }
 }
        eRet = use_buffer(hComp,params->bufferHeader,params->nPortIndex,data,handle->size,buffer);
 } else {
        eRet = OMX_ErrorBadParameter;
 }
 return eRet;
}
