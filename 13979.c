void WebContentsImpl::ResumeLoadingCreatedWebContents() {
  if (delayed_open_url_params_.get()) {
    OpenURL(*delayed_open_url_params_.get());
    delayed_open_url_params_.reset(nullptr);
    return;
  }

  if (is_resume_pending_) {
    is_resume_pending_ = false;
    GetRenderViewHost()->GetWidget()->Init();
    GetMainFrame()->Init();
  }
}
