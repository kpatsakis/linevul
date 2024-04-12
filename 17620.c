void PageHandler::ScreencastFrameEncoded(
    std::unique_ptr<Page::ScreencastFrameMetadata> page_metadata,
    const std::string& data) {
  if (data.empty()) {
    --frames_in_flight_;
    return;  // Encode failed.
  }

  frontend_->ScreencastFrame(data, std::move(page_metadata), session_id_);
}
