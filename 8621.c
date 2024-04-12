  DownloadManagerTest()
      : ui_thread_(content::BrowserThread::UI, &message_loop_),
        file_thread_(content::BrowserThread::FILE, &message_loop_),
        next_download_id_(0) {
  }
