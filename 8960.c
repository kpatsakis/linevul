void DevToolsUIBindings::SetIsDocked(const DispatchCallback& callback,
                                     bool dock_requested) {
  delegate_->SetIsDocked(dock_requested);
  callback.Run(nullptr);
}
