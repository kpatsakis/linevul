void ServiceManagerConnection::DestroyForProcess() {
  g_connection_for_process.Get().reset();
}
