bool FrameLoader::ShouldTreatURLAsSrcdocDocument(const KURL& url) const {
  if (!url.IsAboutSrcdocURL())
    return false;
  HTMLFrameOwnerElement* owner_element = frame_->DeprecatedLocalOwner();
  if (!IsHTMLIFrameElement(owner_element))
    return false;
  return owner_element->FastHasAttribute(kSrcdocAttr);
}
