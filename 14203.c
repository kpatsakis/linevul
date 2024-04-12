  gfx::Image CreateBitmap(SkColor color) {
    SkBitmap thumbnail;
    thumbnail.allocN32Pixels(4, 4);
    thumbnail.eraseColor(color);
    return gfx::Image::CreateFrom1xBitmap(thumbnail);  // adds ref.
  }
