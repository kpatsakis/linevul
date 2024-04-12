void HTMLCanvasElement::NotifyListenersCanvasChanged() {
  if (listeners_.size() == 0)
    return;

  if (!OriginClean()) {
    listeners_.clear();
    return;
  }

  bool listener_needs_new_frame_capture = false;
  for (const CanvasDrawListener* listener : listeners_) {
    if (listener->NeedsNewFrame())
      listener_needs_new_frame_capture = true;
  }

  if (listener_needs_new_frame_capture) {
    SourceImageStatus status;
    scoped_refptr<Image> source_image =
        GetSourceImageForCanvas(&status, kPreferNoAcceleration, FloatSize());
    if (status != kNormalSourceImageStatus)
      return;
    sk_sp<SkImage> image =
        source_image->PaintImageForCurrentFrame().GetSkImage();
    for (CanvasDrawListener* listener : listeners_) {
      if (listener->NeedsNewFrame())
        listener->SendNewFrame(image, source_image->ContextProviderWrapper());
    }
  }
}
