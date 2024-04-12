std::string DownloadItemImpl::DebugString(bool verbose) const {
  std::string description =
      base::StringPrintf("{ id = %d"
                         " state = %s",
                         download_id_.local(),
                         DebugDownloadStateString(GetState()));

  std::string url_list("<none>");
  if (!url_chain_.empty()) {
    std::vector<GURL>::const_iterator iter = url_chain_.begin();
    std::vector<GURL>::const_iterator last = url_chain_.end();
    url_list = (*iter).spec();
    ++iter;
    for ( ; verbose && (iter != last); ++iter) {
      url_list += " ->\n\t";
      const GURL& next_url = *iter;
      url_list += next_url.spec();
    }
  }

  if (verbose) {
    description += base::StringPrintf(
        " db_handle = %" PRId64
        " total = %" PRId64
        " received = %" PRId64
        " reason = %s"
        " paused = %c"
        " otr = %c"
        " safety = %s"
        " last_modified = '%s'"
        " etag = '%s'"
        " url_chain = \n\t\"%s\"\n\t"
        " full_path = \"%" PRFilePath "\""
        " target_path = \"%" PRFilePath "\"",
        GetDbHandle(),
        GetTotalBytes(),
        GetReceivedBytes(),
        InterruptReasonDebugString(last_reason_).c_str(),
        IsPaused() ? 'T' : 'F',
        IsOtr() ? 'T' : 'F',
        DebugSafetyStateString(GetSafetyState()),
        GetLastModifiedTime().c_str(),
        GetETag().c_str(),
        url_list.c_str(),
        GetFullPath().value().c_str(),
        GetTargetFilePath().value().c_str());
  } else {
    description += base::StringPrintf(" url = \"%s\"", url_list.c_str());
  }

  description += " }";

  return description;
}
