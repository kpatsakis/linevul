 void SetFrameBuffer(int idx, vpx_codec_frame_buffer_t *fb) {
    ASSERT_TRUE(fb != NULL);
    fb->data = ext_fb_list_[idx].data;
    fb->size = ext_fb_list_[idx].size;
    ASSERT_EQ(0, ext_fb_list_[idx].in_use);
    ext_fb_list_[idx].in_use = 1;
    fb->priv = &ext_fb_list_[idx];
 }
