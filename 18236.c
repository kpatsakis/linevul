LayerTreeHostImpl::ProcessLayerTreeMutations() {
  std::unique_ptr<BeginFrameCallbackList> callbacks(new BeginFrameCallbackList);
  if (mutator_) {
    const base::Closure& callback = mutator_->TakeMutations();
    if (!callback.is_null())
      callbacks->push_back(callback);
  }
  return callbacks;
}
