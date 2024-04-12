void ResourceMessageFilter::OnRendererTcmalloc(base::ProcessId pid,
                                               const std::string& output) {
  ChromeThread::PostTask(
      ChromeThread::UI, FROM_HERE,
      NewRunnableFunction(AboutTcmallocRendererCallback, pid, output));
}
