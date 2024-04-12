  void SetOnConnected(
      const base::Callback<void(SocketStreamEvent*)>& callback) {
    on_connected_ = callback;
  }
