std::string GetDownloadTypeNames(DownloadItem::DownloadType type) {
  switch (type) {
    case DownloadItem::TYPE_ACTIVE_DOWNLOAD:
      return "NEW_DOWNLOAD";
    case DownloadItem::TYPE_HISTORY_IMPORT:
      return "HISTORY_IMPORT";
    case DownloadItem::TYPE_SAVE_PAGE_AS:
      return "SAVE_PAGE_AS";
    default:
      NOTREACHED();
      return "INVALID_TYPE";
  }
}
