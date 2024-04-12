bool SyncTest::TearDownLocalPythonTestServer() {
  if (!sync_server_.Stop()) {
    LOG(ERROR) << "Could not stop local python test server.";
    return false;
  }
  xmpp_port_.reset();
  return true;
}
