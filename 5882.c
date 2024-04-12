void DownloadItemImpl::SetDangerType(DownloadDangerType danger_type) {
  if (danger_type != danger_type_) {
    TRACE_EVENT_INSTANT1("download", "DownloadItemSaftyStateUpdated",
                         TRACE_EVENT_SCOPE_THREAD, "danger_type",
                         GetDownloadDangerNames(danger_type).c_str());
  }
  if ((danger_type_ == DOWNLOAD_DANGER_TYPE_NOT_DANGEROUS ||
       danger_type_ == DOWNLOAD_DANGER_TYPE_DANGEROUS_FILE ||
       danger_type_ == DOWNLOAD_DANGER_TYPE_UNCOMMON_CONTENT ||
       danger_type_ == DOWNLOAD_DANGER_TYPE_MAYBE_DANGEROUS_CONTENT) &&
      (danger_type == DOWNLOAD_DANGER_TYPE_DANGEROUS_HOST ||
       danger_type == DOWNLOAD_DANGER_TYPE_DANGEROUS_URL ||
       danger_type == DOWNLOAD_DANGER_TYPE_DANGEROUS_CONTENT ||
       danger_type == DOWNLOAD_DANGER_TYPE_POTENTIALLY_UNWANTED)) {
    RecordMaliciousDownloadClassified(danger_type);
  }
  danger_type_ = danger_type;
}
