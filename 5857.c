  void CheckServerReachable() {
    if (connection_manager()) {
      connection_manager()->CheckServerReachable();
    } else {
      NOTREACHED() << "Should be valid connection manager!";
    }
  }
