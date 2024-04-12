  void GetStatusCallback(AppCacheStatus status, void* param) {
    last_status_result_ = status;
    last_callback_param_ = param;
  }
