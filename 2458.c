  explicit CustomNTPUrlTest(const std::string& ntp_file_path)
      : https_test_server_(net::EmbeddedTestServer::TYPE_HTTPS),
        ntp_file_path_(ntp_file_path) {
    https_test_server_.ServeFilesFromSourceDirectory(
        "chrome/test/data/local_ntp");
  }
