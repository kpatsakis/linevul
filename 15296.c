  void SetOnReceivedData(
      const base::Callback<void(SocketStreamEvent*)>& callback) {
    on_received_data_ = callback;
  }
