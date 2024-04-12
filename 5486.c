DownloadPathReservationTrackerTest::GetLongNamePathInDownloadsDirectory(
    size_t repeat, const base::FilePath::CharType* suffix) {
  return GetPathInDownloadsDirectory(
      (base::FilePath::StringType(repeat, FILE_PATH_LITERAL('a'))
          + suffix).c_str());
}
