void FileReaderLoader::OnComplete(int32_t status, uint64_t data_length) {
  DEFINE_THREAD_SAFE_STATIC_LOCAL(SparseHistogram,
                                  file_reader_loader_read_errors_histogram,
                                  ("Storage.Blob.FileReaderLoader.ReadError"));
  if (status != net::OK) {
    net_error_ = status;
    file_reader_loader_read_errors_histogram.Sample(std::max(0, -net_error_));
    Failed(status == net::ERR_FILE_NOT_FOUND ? FileErrorCode::kNotFoundErr
                                             : FileErrorCode::kNotReadableErr,
           FailureType::kBackendReadError);
    return;
  }
  if (data_length != total_bytes_) {
    Failed(FileErrorCode::kNotReadableErr, FailureType::kReadSizesIncorrect);
    return;
  }

  received_on_complete_ = true;
  if (received_all_data_)
    OnFinishLoading();
}
