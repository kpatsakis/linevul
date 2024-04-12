  ~ScopedUnpackStateButAlignmentReset() {
    if (skip_pixels_ != 0) {
      api_->glPixelStoreiFn(GL_UNPACK_SKIP_PIXELS, skip_pixels_);
    }
    if (skip_rows_ != 0) {
      api_->glPixelStoreiFn(GL_UNPACK_SKIP_ROWS, skip_rows_);
    }
    if (skip_images_ != 0) {
      api_->glPixelStoreiFn(GL_UNPACK_SKIP_IMAGES, skip_images_);
    }
    if (row_length_ != 0) {
      api_->glPixelStoreiFn(GL_UNPACK_ROW_LENGTH, row_length_);
    }
    if (image_height_ != 0) {
      api_->glPixelStoreiFn(GL_UNPACK_IMAGE_HEIGHT, image_height_);
    }
  }
