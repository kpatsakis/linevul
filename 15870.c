LayerTreeHost::~LayerTreeHost() {
  CHECK(!inside_main_frame_);
  TRACE_EVENT0("cc", "LayerTreeHostInProcess::~LayerTreeHostInProcess");

  mutator_host_->SetMutatorHostClient(nullptr);

  RegisterViewportLayers(nullptr, nullptr, nullptr, nullptr);

  if (root_layer_) {
    root_layer_->SetLayerTreeHost(nullptr);

    root_layer_ = nullptr;
  }

  if (proxy_) {
    DCHECK(task_runner_provider_->IsMainThread());
    proxy_->Stop();

    proxy_ = nullptr;
  }
}
