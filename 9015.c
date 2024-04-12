void RenderMessageFilter::OnGetProcessMemorySizes(
    size_t* private_bytes, size_t* shared_bytes) {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::IO));
  using base::ProcessMetrics;
#if !defined(OS_MACOSX) || defined(OS_IOS)
  scoped_ptr<ProcessMetrics> metrics(
      ProcessMetrics::CreateProcessMetrics(peer_handle()));
#else
  scoped_ptr<ProcessMetrics> metrics(
      ProcessMetrics::CreateProcessMetrics(peer_handle(), NULL));
#endif
  metrics->GetMemoryBytes(private_bytes, shared_bytes);
}
