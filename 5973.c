 void CheckXImageFrameBuffer(const vpx_image_t *img) {
 if (img->fb_priv != NULL) {
 const struct ExternalFrameBuffer *const ext_fb =
 reinterpret_cast<ExternalFrameBuffer*>(img->fb_priv);

      ASSERT_TRUE(img->planes[0] >= ext_fb->data &&
                  img->planes[0] < (ext_fb->data + ext_fb->size));
 }
 }
