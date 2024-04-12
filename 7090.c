bool LayerTreeHost::IsThreaded() const {
  DCHECK(compositor_mode_ != CompositorMode::THREADED ||
         task_runner_provider_->HasImplThread());
  return compositor_mode_ == CompositorMode::THREADED;
}
