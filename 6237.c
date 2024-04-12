  virtual void RunCallback() {
    callback_->Run(error_code(), base::PassPlatformFile(&file_handle_),
                   file_path_);
    delete callback_;
  }
