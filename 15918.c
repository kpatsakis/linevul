unsigned venc_dev::venc_stop( void)
{
 struct venc_msg venc_msg;
 struct v4l2_requestbuffers bufreq;
 int rc = 0, ret = 0;

 if (!stopped) {
 enum v4l2_buf_type cap_type;

 if (streaming[OUTPUT_PORT]) {
            cap_type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE;
            rc = ioctl(m_nDriver_fd, VIDIOC_STREAMOFF, &cap_type);

 if (rc) {
                DEBUG_PRINT_ERROR("Failed to call streamoff on driver: capability: %d, %d",
                        cap_type, rc);
 } else
                streaming[OUTPUT_PORT] = false;

            DEBUG_PRINT_LOW("Releasing registered buffers from driver on o/p port");
            bufreq.memory = V4L2_MEMORY_USERPTR;
            bufreq.count = 0;
            bufreq.type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE;
            ret = ioctl(m_nDriver_fd, VIDIOC_REQBUFS, &bufreq);

 if (ret) {
                DEBUG_PRINT_ERROR("ERROR: VIDIOC_REQBUFS OUTPUT MPLANE Failed");
 return false;
 }
 }

 if (!rc && streaming[CAPTURE_PORT]) {
            cap_type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
            rc = ioctl(m_nDriver_fd, VIDIOC_STREAMOFF, &cap_type);

 if (rc) {
                DEBUG_PRINT_ERROR("Failed to call streamoff on driver: capability: %d, %d",
                        cap_type, rc);
 } else
                streaming[CAPTURE_PORT] = false;

            DEBUG_PRINT_LOW("Releasing registered buffers from driver on capture port");
            bufreq.memory = V4L2_MEMORY_USERPTR;
            bufreq.count = 0;
            bufreq.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
            ret = ioctl(m_nDriver_fd, VIDIOC_REQBUFS, &bufreq);

 if (ret) {
                DEBUG_PRINT_ERROR("ERROR: VIDIOC_REQBUFS CAPTURE MPLANE Failed");
 return false;
 }
 }

 if (!rc && !ret) {
            venc_stop_done();
            stopped = 1;
 /*set flag to re-configure when started again*/
            resume_in_stopped = 1;

 }
 }

 return rc;
}
