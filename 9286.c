  virtual void RunWork() {
    if (!file_util::PathExists(file_path_)) {
      set_error_code(base::PLATFORM_FILE_ERROR_NOT_FOUND);
      return;
    }
    if (!file_util::Delete(file_path_, recursive_)) {
      if (!recursive_ && !file_util::IsDirectoryEmpty(file_path_)) {
        set_error_code(base::PLATFORM_FILE_ERROR_NOT_EMPTY);
        return;
      }
      set_error_code(base::PLATFORM_FILE_ERROR_FAILED);
    }
  }
