  RelayTruncate(const FilePath& path,
                int64 length,
                base::FileUtilProxy::StatusCallback* callback)
      : RelayWithStatusCallback(callback),
        path_(path),
        length_(length) {
  }
