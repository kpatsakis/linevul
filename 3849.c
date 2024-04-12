void RecordDownloadVideoType(const std::string& mime_type_string) {
  DownloadVideo download_video = DownloadVideo(
      GetMimeTypeMatch(mime_type_string, getMimeTypeToDownloadVideoMap()));
  UMA_HISTOGRAM_ENUMERATION("Download.ContentType.Video", download_video,
                            DOWNLOAD_VIDEO_MAX);
}
