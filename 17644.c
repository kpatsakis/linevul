bool SyncerProtoUtil::PostAndProcessHeaders(ServerConnectionManager* scm,
                                            sessions::SyncSession* session,
                                            const ClientToServerMessage& msg,
                                            ClientToServerResponse* response) {

  ServerConnectionManager::PostBufferParams params;
  msg.SerializeToString(&params.buffer_in);

  ScopedServerStatusWatcher server_status_watcher(scm, &params.response);
  if (!scm->PostBufferWithCachedAuth(&params, &server_status_watcher)) {
    LOG(WARNING) << "Error posting from syncer:" << params.response;
    return false;
  }

  std::string new_token = params.response.update_client_auth_header;
  if (!new_token.empty()) {
    SyncEngineEvent event(SyncEngineEvent::UPDATED_TOKEN);
    event.updated_token = new_token;
    session->context()->NotifyListeners(event);
  }

  if (response->ParseFromString(params.buffer_out)) {
    switch (response->error_code()) {
      case ClientToServerResponse::ACCESS_DENIED:
      case ClientToServerResponse::AUTH_INVALID:
      case ClientToServerResponse::USER_NOT_ACTIVATED:
        params.response.server_status = HttpResponse::SYNC_AUTH_ERROR;
        return false;
      default:
        return true;
    }
  }

  return false;
}
