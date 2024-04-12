bool NavigationControllerImpl::NavigateToPendingEntryInternal(
    ReloadType reload_type,
    std::unique_ptr<NavigationUIData> navigation_ui_data) {
  DCHECK(pending_entry_);
  FrameTreeNode* root = delegate_->GetFrameTree()->root();

  FrameLoadVector same_document_loads;
  FrameLoadVector different_document_loads;
  if (GetLastCommittedEntry()) {
    FindFramesToNavigate(root, &same_document_loads, &different_document_loads);
  }

  if (same_document_loads.empty() && different_document_loads.empty()) {
    different_document_loads.push_back(
        std::make_pair(root, pending_entry_->GetFrameEntry(root)));
  }

  bool success = false;

  for (const auto& item : same_document_loads) {
    FrameTreeNode* frame = item.first;
    DCHECK(!IsRendererDebugURL(item.second->url()));
    std::unique_ptr<NavigationRequest> request = CreateNavigationRequest(
        frame, *pending_entry_, item.second, reload_type,
        true /* is_same_document_history_load */,
        false /* is_history_navigation_in_new_child */, nullptr, nullptr);
    if (request) {
      success = true;
      frame->navigator()->Navigate(std::move(request), reload_type,
                                   pending_entry_->restore_type());
    }
  }
  for (const auto& item : different_document_loads) {
    FrameTreeNode* frame = item.first;
    if (IsRendererDebugURL(item.second->url())) {
      HandleRendererDebugURL(frame, item.second->url());
      if (!item.second->url().SchemeIs(url::kJavaScriptScheme)) {
        success = true;
      }
    } else {
      std::unique_ptr<NavigationRequest> request = CreateNavigationRequest(
          frame, *pending_entry_, item.second, reload_type,
          false /* is_same_document_history_load */,
          false /* is_history_navigation_in_new_child */, nullptr,
          frame->IsMainFrame() ? std::move(navigation_ui_data) : nullptr);
      if (request) {
        success = true;
        frame->navigator()->Navigate(std::move(request), reload_type,
                                     pending_entry_->restore_type());
      }
    }
  }
  return success;
}
