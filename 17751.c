void RenderThreadImpl::RemoveEmbeddedWorkerRoute(int32_t routing_id) {
  RemoveRoute(routing_id);
  if (devtools_agent_message_filter_.get()) {
    devtools_agent_message_filter_->RemoveEmbeddedWorkerRouteOnMainThread(
        routing_id);
  }
}
