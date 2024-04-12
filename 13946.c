void Document::SetURL(const KURL& url) {
  const KURL& new_url = url.IsEmpty() ? BlankURL() : url;
  if (new_url == url_)
    return;

  url_ = new_url;
  access_entry_from_url_ = nullptr;
  UpdateBaseURL();
  GetContextFeatures().UrlDidChange(this);

  if (ukm_recorder_ && IsInMainFrame())
    ukm_recorder_->UpdateSourceURL(ukm_source_id_, url_);
}
