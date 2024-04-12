OMX_ERRORTYPE omx_vdec::set_buffer_req(vdec_allocatorproperty *buffer_prop)
{
    OMX_ERRORTYPE eRet = OMX_ErrorNone;
 unsigned buf_size = 0;
 struct v4l2_format fmt;
 struct v4l2_requestbuffers bufreq;
 int ret;
    DEBUG_PRINT_LOW("SetBufReq IN: ActCnt(%d) Size(%u)",
            buffer_prop->actualcount, (unsigned int)buffer_prop->buffer_size);
    buf_size = (buffer_prop->buffer_size + buffer_prop->alignment - 1)&(~(buffer_prop->alignment - 1));
 if (buf_size != buffer_prop->buffer_size) {
        DEBUG_PRINT_ERROR("Buffer size alignment error: Requested(%u) Required(%d)",
 (unsigned int)buffer_prop->buffer_size, buf_size);
        eRet = OMX_ErrorBadParameter;
 } else {
        memset(&fmt, 0x0, sizeof(struct v4l2_format));
        fmt.fmt.pix_mp.height = drv_ctx.video_resolution.frame_height;
        fmt.fmt.pix_mp.width = drv_ctx.video_resolution.frame_width;

 if (buffer_prop->buffer_type == VDEC_BUFFER_TYPE_INPUT) {
            fmt.type =V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE;
            fmt.fmt.pix_mp.pixelformat = output_capability;
            fmt.fmt.pix_mp.plane_fmt[0].sizeimage = buf_size;
 } else if (buffer_prop->buffer_type == VDEC_BUFFER_TYPE_OUTPUT) {
            fmt.type =V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
            fmt.fmt.pix_mp.pixelformat = capture_capability;
 } else {
            eRet = OMX_ErrorBadParameter;
 }

        ret = ioctl(drv_ctx.video_driver_fd, VIDIOC_S_FMT, &fmt);
 if (ret) {
 /*TODO: How to handle this case */
            DEBUG_PRINT_ERROR("Setting buffer requirements (format) failed %d", ret);
            eRet = OMX_ErrorInsufficientResources;
 }

        bufreq.memory = V4L2_MEMORY_USERPTR;
        bufreq.count = buffer_prop->actualcount;
 if (buffer_prop->buffer_type == VDEC_BUFFER_TYPE_INPUT) {
            bufreq.type=V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE;
 } else if (buffer_prop->buffer_type == VDEC_BUFFER_TYPE_OUTPUT) {
            bufreq.type=V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
 } else {
            eRet = OMX_ErrorBadParameter;
 }

 if (eRet==OMX_ErrorNone) {
            ret = ioctl(drv_ctx.video_driver_fd,VIDIOC_REQBUFS, &bufreq);
 }

 if (ret) {
            DEBUG_PRINT_ERROR("Setting buffer requirements (reqbufs) failed %d", ret);
 /*TODO: How to handle this case */
            eRet = OMX_ErrorInsufficientResources;
 } else if (bufreq.count < buffer_prop->actualcount) {
            DEBUG_PRINT_ERROR("Driver refused to change the number of buffers"
 " on v4l2 port %d to %d (prefers %d)", bufreq.type,
                    buffer_prop->actualcount, bufreq.count);
            eRet = OMX_ErrorInsufficientResources;
 } else {
 if (!client_buffers.update_buffer_req()) {
                DEBUG_PRINT_ERROR("Setting c2D buffer requirements failed");
                eRet = OMX_ErrorInsufficientResources;
 }
 }
 }
 return eRet;
}
