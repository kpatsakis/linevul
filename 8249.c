  HttpNetworkTransactionTest()
      : ssl_(ASYNC, OK),
        old_max_group_sockets_(ClientSocketPoolManager::max_sockets_per_group(
            HttpNetworkSession::NORMAL_SOCKET_POOL)),
        old_max_pool_sockets_(ClientSocketPoolManager::max_sockets_per_pool(
            HttpNetworkSession::NORMAL_SOCKET_POOL)) {
    session_deps_.enable_http2_alternative_service = true;
  }
