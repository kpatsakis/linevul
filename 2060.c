  SyncBackendHostTest()
      : ui_thread_(BrowserThread::UI, &ui_loop_),
        io_thread_(BrowserThread::IO) {}
