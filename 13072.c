void LayerTreeHostImpl::EvictAllUIResources() {
  if (ui_resource_map_.empty())
    return;
  ClearUIResources();

  client_->SetNeedsCommitOnImplThread();
  client_->OnCanDrawStateChanged(CanDraw());
  client_->RenewTreePriority();
}
