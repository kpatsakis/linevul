String FileReaderLoader::StringResult() {
  DCHECK_NE(read_type_, kReadAsArrayBuffer);
  DCHECK_NE(read_type_, kReadByClient);

  if (!raw_data_ || error_code_ || is_raw_data_converted_)
    return string_result_;

  switch (read_type_) {
    case kReadAsArrayBuffer:
      return string_result_;
    case kReadAsBinaryString:
      SetStringResult(raw_data_->ToString());
      break;
    case kReadAsText:
      SetStringResult(ConvertToText());
      break;
    case kReadAsDataURL:
      if (finished_loading_)
        SetStringResult(ConvertToDataURL());
      break;
    default:
      NOTREACHED();
  }

  if (finished_loading_) {
    DCHECK(is_raw_data_converted_);
    AdjustReportedMemoryUsageToV8(
        -1 * static_cast<int64_t>(raw_data_->ByteLength()));
    raw_data_.reset();
  }
  return string_result_;
}
