base::FilePath DownloadPathReservationTrackerTest::GetPathInDownloadsDirectory(
    const base::FilePath::CharType* suffix) {
  return default_download_path().Append(suffix).NormalizePathSeparators();
}
