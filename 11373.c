void RecordDownloadCountWithSource(DownloadCountTypes type,
                                   DownloadSource download_source) {
  RecordDownloadCount(type);

  std::string name =
      CreateHistogramNameWithSuffix("Download.Counts", download_source);
  base::UmaHistogramEnumeration(name, type, DOWNLOAD_COUNT_TYPES_LAST_ENTRY);
}
