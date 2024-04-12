void TracingControllerImpl::OnTraceLogEnabled() {
  if (start_tracing_done_)
    std::move(start_tracing_done_).Run();
}
