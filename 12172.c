void RenderFrameHostImpl::SetNavigationRequest(
    std::unique_ptr<NavigationRequest> navigation_request) {
  DCHECK(navigation_request);
  if (FrameMsg_Navigate_Type::IsSameDocument(
          navigation_request->common_params().navigation_type)) {
    same_document_navigation_request_ = std::move(navigation_request);
    return;
  }
  navigation_request_ = std::move(navigation_request);
}
