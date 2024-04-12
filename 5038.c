void HTMLMediaElement::CloseMediaSource() {
  if (!media_source_)
    return;

  media_source_->Close();
  media_source_ = nullptr;
}
