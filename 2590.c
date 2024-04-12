  virtual void RunWork() {
    if (!base::ClosePlatformFile(file_handle_))
      set_error_code(base::PLATFORM_FILE_ERROR_FAILED);
  }
