  void NotifySessionStateChanged(session_manager::SessionState state) {
    GetSessionControllerClient()->SetSessionState(state);
  }
