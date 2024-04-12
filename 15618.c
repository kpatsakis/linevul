unsigned venc_dev::venc_flush( unsigned port)
{
 struct v4l2_encoder_cmd enc;
    DEBUG_PRINT_LOW("in %s", __func__);

    enc.cmd = V4L2_ENC_QCOM_CMD_FLUSH;
    enc.flags = V4L2_QCOM_CMD_FLUSH_OUTPUT | V4L2_QCOM_CMD_FLUSH_CAPTURE;

 if (ioctl(m_nDriver_fd, VIDIOC_ENCODER_CMD, &enc)) {
        DEBUG_PRINT_ERROR("Flush Port (%d) Failed ", port);
 return -1;
 }

 return 0;

}
