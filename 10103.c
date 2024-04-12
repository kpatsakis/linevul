int FrameFetchContext::ApplicationCacheHostID() const {
  if (!document_loader_)
    return WebApplicationCacheHost::kAppCacheNoHostId;
  return document_loader_->GetApplicationCacheHost()->GetHostID();
}
