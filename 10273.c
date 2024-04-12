  FileProxyTest()
      : file_thread_("FileProxyTestFileThread"),
        error_(File::FILE_OK),
        bytes_written_(-1),
        weak_factory_(this) {}
