DownloadInterruptReason CallbackAndReturn(
    const DownloadUrlParameters::OnStartedCallback& started_cb,
    DownloadInterruptReason interrupt_reason) {
  if (started_cb.is_null())
    return interrupt_reason;
  BrowserThread::PostTask(
      BrowserThread::UI,
      FROM_HERE,
      base::Bind(
          started_cb, static_cast<DownloadItem*>(NULL), interrupt_reason));

  return interrupt_reason;
}
