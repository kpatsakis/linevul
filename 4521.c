DownloadFileManager::DownloadFileManager(DownloadFileFactory* factory)
    : download_file_factory_(factory) {
  if (download_file_factory_ == NULL)
    download_file_factory_.reset(new DownloadFileFactoryImpl);
}
