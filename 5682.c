MessageLoop* BrowserGpuChannelHostFactory::GetMainLoop() {
  return BrowserThread::UnsafeGetMessageLoopForThread(BrowserThread::UI);
}
