  void SetHeader(const std::string& header) {
    base::AutoLock auto_lock(lock_);
    header_ = header;
  }
