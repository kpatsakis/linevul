void CSSStyleSheet::SetLoadCompleted(bool completed) {
  if (completed == load_completed_)
    return;

  load_completed_ = completed;

  if (completed)
    contents_->ClientLoadCompleted(this);
  else
    contents_->ClientLoadStarted(this);
}
