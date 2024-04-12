void SoftMPEG4Encoder::initPorts() {
    OMX_PARAM_PORTDEFINITIONTYPE def;
 InitOMXParams(&def);

 const size_t kInputBufferSize = (mVideoWidth * mVideoHeight * 3) >> 1;

 const size_t kOutputBufferSize =
 (kInputBufferSize > 256 * 1024)
 ? kInputBufferSize: 256 * 1024;

    def.nPortIndex = 0;
    def.eDir = OMX_DirInput;
    def.nBufferCountMin = kNumBuffers;
    def.nBufferCountActual = def.nBufferCountMin;
    def.nBufferSize = kInputBufferSize;
    def.bEnabled = OMX_TRUE;
    def.bPopulated = OMX_FALSE;
    def.eDomain = OMX_PortDomainVideo;
    def.bBuffersContiguous = OMX_FALSE;
    def.nBufferAlignment = 1;

    def.format.video.cMIMEType = const_cast<char *>("video/raw");

    def.format.video.eCompressionFormat = OMX_VIDEO_CodingUnused;
    def.format.video.eColorFormat = OMX_COLOR_FormatYUV420Planar;
    def.format.video.xFramerate = (mVideoFrameRate << 16); // Q16 format
    def.format.video.nBitrate = mVideoBitRate;
    def.format.video.nFrameWidth = mVideoWidth;
    def.format.video.nFrameHeight = mVideoHeight;
    def.format.video.nStride = mVideoWidth;
    def.format.video.nSliceHeight = mVideoHeight;

    addPort(def);

    def.nPortIndex = 1;
    def.eDir = OMX_DirOutput;
    def.nBufferCountMin = kNumBuffers;
    def.nBufferCountActual = def.nBufferCountMin;
    def.nBufferSize = kOutputBufferSize;
    def.bEnabled = OMX_TRUE;
    def.bPopulated = OMX_FALSE;
    def.eDomain = OMX_PortDomainVideo;
    def.bBuffersContiguous = OMX_FALSE;
    def.nBufferAlignment = 2;

    def.format.video.cMIMEType =
 (mEncodeMode == COMBINE_MODE_WITH_ERR_RES)
 ? const_cast<char *>(MEDIA_MIMETYPE_VIDEO_MPEG4)
 : const_cast<char *>(MEDIA_MIMETYPE_VIDEO_H263);

    def.format.video.eCompressionFormat =
 (mEncodeMode == COMBINE_MODE_WITH_ERR_RES)
 ? OMX_VIDEO_CodingMPEG4
 : OMX_VIDEO_CodingH263;

    def.format.video.eColorFormat = OMX_COLOR_FormatUnused;
    def.format.video.xFramerate = (0 << 16); // Q16 format
    def.format.video.nBitrate = mVideoBitRate;
    def.format.video.nFrameWidth = mVideoWidth;
    def.format.video.nFrameHeight = mVideoHeight;
    def.format.video.nStride = mVideoWidth;
    def.format.video.nSliceHeight = mVideoHeight;

    addPort(def);
}
