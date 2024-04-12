  virtual ~RelayCreateTemporary() {
    if (file_handle_ != base::kInvalidPlatformFileValue)
      base::FileUtilProxy::Close(message_loop_proxy_, file_handle_, NULL);
  }
