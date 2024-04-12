void RendererSchedulerImpl::SetRendererProcessType(RendererProcessType type) {
  main_thread_only().process_type = type;
}
