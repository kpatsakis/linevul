void FileReaderLoader::Failed(FileErrorCode error_code, FailureType type) {
  DEFINE_THREAD_SAFE_STATIC_LOCAL(EnumerationHistogram, failure_histogram,
                                  ("Storage.Blob.FileReaderLoader.FailureType",
                                   static_cast<int>(FailureType::kCount)));
  if (error_code_ != FileErrorCode::kOK)
    return;
  error_code_ = error_code;
  failure_histogram.Count(static_cast<int>(type));
  Cleanup();
  if (client_)
    client_->DidFail(error_code_);
}
