void FrameLoader::DispatchUnloadEvent() {
  FrameNavigationDisabler navigation_disabler(*frame_);

  protect_provisional_loader_ = false;
  SaveScrollState();

  if (frame_->GetDocument() && !SVGImage::IsInSVGImage(frame_->GetDocument()))
    frame_->GetDocument()->DispatchUnloadEvents();
}
