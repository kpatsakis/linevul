void DevToolsSession::MojoConnectionDestroyed() {
  binding_.Close();
  session_ptr_.reset();
  io_session_ptr_.reset();
}
