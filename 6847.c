int32_t WebContentsImpl::GetMaxPageID() {
  return GetMaxPageIDForSiteInstance(GetSiteInstance());
}
