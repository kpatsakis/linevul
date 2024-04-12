OMX_ERRORTYPE  omx_video::use_EGL_image(OMX_IN OMX_HANDLETYPE   hComp,
        OMX_INOUT OMX_BUFFERHEADERTYPE** bufferHdr,
        OMX_IN OMX_U32                        port,
        OMX_IN OMX_PTR                     appData,
        OMX_IN void*                      eglImage)
{
 (void)hComp, (void)bufferHdr, (void)port, (void)appData, (void)eglImage;
    DEBUG_PRINT_ERROR("ERROR: use_EGL_image:  Not Implemented");
 return OMX_ErrorNotImplemented;
}
