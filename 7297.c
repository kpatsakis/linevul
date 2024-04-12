  void ShutDown() {
    BrowserThread::GetTaskRunnerForThread(BrowserThread::IO)->PostTask(
        FROM_HERE,
        base::Bind(&InProcessServiceManagerContext::ShutDownOnIOThread, this));
  }
