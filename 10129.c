RenderFrameSubmissionObserver::RenderFrameSubmissionObserver(
    RenderFrameMetadataProvider* render_frame_metadata_provider)
    : render_frame_metadata_provider_(render_frame_metadata_provider) {
  render_frame_metadata_provider_->AddObserver(this);
  render_frame_metadata_provider_->ReportAllFrameSubmissionsForTesting(true);
}
