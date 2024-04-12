 virtual void PreDecodeFrameHook(
 const libvpx_test::CompressedVideoSource &video,
      libvpx_test::Decoder *decoder) {
 if (num_buffers_ > 0 && video.frame_number() == 0) {
      ASSERT_TRUE(fb_list_.CreateBufferList(num_buffers_));
      ASSERT_EQ(VPX_CODEC_OK,
                decoder->SetFrameBufferFunctions(
 GetVP9FrameBuffer, ReleaseVP9FrameBuffer, this));
 }
 }
