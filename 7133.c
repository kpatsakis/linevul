bool venc_dev::venc_set_useltr(OMX_U32 frameIdx)
{
    DEBUG_PRINT_LOW("venc_use_goldenframe");
 int rc = true;
 struct v4l2_control control;

    control.id = V4L2_CID_MPEG_VIDC_VIDEO_USELTRFRAME;
    control.value = frameIdx;

    rc = ioctl(m_nDriver_fd, VIDIOC_S_CTRL, &control);
 if (rc) {
        DEBUG_PRINT_ERROR("Failed to set use_ltr %d", rc);
 return false;
 }

    DEBUG_PRINT_LOW("Success IOCTL set control for id=%x, val=%d",
                    control.id, control.value);
 return true;
}
