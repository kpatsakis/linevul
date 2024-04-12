ImageBitmap::ImageBitmap(HTMLVideoElement* video,
                         Optional<IntRect> cropRect,
                         Document* document,
                         const ImageBitmapOptions& options) {
  IntSize playerSize;
  if (video->webMediaPlayer())
    playerSize = video->webMediaPlayer()->naturalSize();
  ParsedOptions parsedOptions =
      parseOptions(options, cropRect, video->bitmapSourceSize());
  if (dstBufferSizeHasOverflow(parsedOptions))
    return;

  std::unique_ptr<ImageBuffer> buffer = ImageBuffer::create(
      IntSize(parsedOptions.resizeWidth, parsedOptions.resizeHeight), NonOpaque,
      DoNotInitializeImagePixels);
  if (!buffer)
    return;

  IntPoint dstPoint =
      IntPoint(-parsedOptions.cropRect.x(), -parsedOptions.cropRect.y());
  if (parsedOptions.flipY) {
    buffer->canvas()->translate(0, buffer->size().height());
    buffer->canvas()->scale(1, -1);
  }
  SkPaint paint;
  if (parsedOptions.shouldScaleInput) {
    float scaleRatioX = static_cast<float>(parsedOptions.resizeWidth) /
                        parsedOptions.cropRect.width();
    float scaleRatioY = static_cast<float>(parsedOptions.resizeHeight) /
                        parsedOptions.cropRect.height();
    buffer->canvas()->scale(scaleRatioX, scaleRatioY);
    paint.setFilterQuality(parsedOptions.resizeQuality);
  }
  buffer->canvas()->translate(dstPoint.x(), dstPoint.y());
  video->paintCurrentFrame(
      buffer->canvas(),
      IntRect(IntPoint(), IntSize(video->videoWidth(), video->videoHeight())),
      parsedOptions.shouldScaleInput ? &paint : nullptr);

  sk_sp<SkImage> skiaImage =
      buffer->newSkImageSnapshot(PreferNoAcceleration, SnapshotReasonUnknown);
  if (!parsedOptions.premultiplyAlpha)
    skiaImage = premulSkImageToUnPremul(skiaImage.get());
  if (!skiaImage)
    return;
  m_image = StaticBitmapImage::create(std::move(skiaImage));
  m_image->setOriginClean(
      !video->wouldTaintOrigin(document->getSecurityOrigin()));
  m_image->setPremultiplied(parsedOptions.premultiplyAlpha);
}
