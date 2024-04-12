cc::TaskGraphRunner* RenderThreadImpl::GetTaskGraphRunner() {
  return categorized_worker_pool_->GetTaskGraphRunner();
}
