void RenderFrameHostImpl::OnCrossDocumentCommitProcessed(
    NavigationRequest* navigation_request,
    blink::mojom::CommitResult result) {
  DCHECK_NE(blink::mojom::CommitResult::RestartCrossDocument, result);
  if (result == blink::mojom::CommitResult::Ok) {
    auto find_request = navigation_requests_.find(navigation_request);
    if (find_request != navigation_requests_.end()) {
      navigation_request_ = std::move(find_request->second);
    } else {
    }
  }
  navigation_requests_.erase(navigation_request);
}
