void ChromeNetworkDelegate::OnRawBytesRead(const net::URLRequest& request,
                                           int bytes_read) {
  TRACE_EVENT_ASYNC_STEP_PAST1("net", "URLRequest", &request, "DidRead",
                               "bytes_read", bytes_read);
  performance_monitor::PerformanceMonitor::GetInstance()->BytesReadOnIOThread(
      request, bytes_read);

#if defined(ENABLE_TASK_MANAGER)
  TaskManager::GetInstance()->model()->NotifyBytesRead(request, bytes_read);
#endif  // defined(ENABLE_TASK_MANAGER)
}
