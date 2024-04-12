void DisplaySourceCustomBindings::OnSessionError(int sink_id,
                                                 DisplaySourceErrorType type,
                                                 const std::string& message) {
  CHECK(GetDisplaySession(sink_id));
  DispatchSessionError(sink_id, type, message);
}
