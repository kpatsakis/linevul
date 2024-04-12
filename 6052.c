void Browser::ActivateContents(WebContents* contents) {
  tab_strip_model_->ActivateTabAt(
      tab_strip_model_->GetIndexOfWebContents(contents), false);
  window_->Activate();
}
