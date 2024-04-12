  bool VerifyNoDownloads() const {
    DownloadManager::DownloadVector items;
    GetDownloads(browser(), &items);
    return items.empty();
  }
