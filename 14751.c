  ProxyBrowserTest()
      : proxy_server_(net::SpawnedTestServer::TYPE_BASIC_AUTH_PROXY,
                      base::FilePath()) {
  }
