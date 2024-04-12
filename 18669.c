  RelayFlush(base::PlatformFile file,
             base::FileUtilProxy::StatusCallback* callback)
      : RelayWithStatusCallback(callback),
        file_(file) {
  }
