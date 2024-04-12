void FileReaderLoader::Cleanup() {
  handle_watcher_.Cancel();
  consumer_handle_.reset();

  if (error_code_ != FileErrorCode::kOK) {
    raw_data_.reset();
    string_result_ = "";
    is_raw_data_converted_ = true;
    decoder_.reset();
    array_buffer_result_ = nullptr;
    UnadjustReportedMemoryUsageToV8();
  }
}
