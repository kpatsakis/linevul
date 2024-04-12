void FileReaderLoader::Failed(FileError::ErrorCode error_code) {
  if (error_code_ != FileError::kOK)
    return;
  error_code_ = error_code;
  Cleanup();
  if (client_)
    client_->DidFail(error_code_);
}
