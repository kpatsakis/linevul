WebFrameLoadType FrameLoader::DetermineFrameLoadType(
    const ResourceRequest& resource_request,
    Document* origin_document,
    const KURL& failing_url,
    WebFrameLoadType frame_load_type) {
  if (frame_load_type == WebFrameLoadType::kStandard ||
      frame_load_type == WebFrameLoadType::kReplaceCurrentItem) {
    if (frame_->Tree().Parent() &&
        !state_machine_.CommittedFirstRealDocumentLoad())
      return WebFrameLoadType::kReplaceCurrentItem;
    if (!frame_->Tree().Parent() && !Client()->BackForwardLength()) {
      if (Opener() && resource_request.Url().IsEmpty())
        return WebFrameLoadType::kReplaceCurrentItem;
      return WebFrameLoadType::kStandard;
    }
  }
  if (frame_load_type != WebFrameLoadType::kStandard)
    return frame_load_type;
  CHECK_NE(mojom::FetchCacheMode::kValidateCache,
           resource_request.GetCacheMode());
  CHECK_NE(mojom::FetchCacheMode::kBypassCache,
           resource_request.GetCacheMode());
  if ((!state_machine_.CommittedMultipleRealLoads() &&
       DeprecatedEqualIgnoringCase(frame_->GetDocument()->Url(), BlankURL())))
    return WebFrameLoadType::kReplaceCurrentItem;

  if (resource_request.Url() == document_loader_->UrlForHistory()) {
    if (resource_request.HttpMethod() == http_names::kPOST)
      return WebFrameLoadType::kStandard;
    if (!origin_document)
      return WebFrameLoadType::kReload;
    return WebFrameLoadType::kReplaceCurrentItem;
  }

  if (failing_url == document_loader_->UrlForHistory() &&
      document_loader_->LoadType() == WebFrameLoadType::kReload)
    return WebFrameLoadType::kReload;

  if (resource_request.Url().IsEmpty() && failing_url.IsEmpty()) {
    return WebFrameLoadType::kReplaceCurrentItem;
  }

  if (origin_document && !origin_document->CanCreateHistoryEntry())
    return WebFrameLoadType::kReplaceCurrentItem;

  return WebFrameLoadType::kStandard;
}
