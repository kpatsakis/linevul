  void OnDataReceivedFromPeer(const char* data, size_t data_len) {
    DCHECK(delegate_);
    delegate_->OnPacketDataReceived(data, data_len);
  }
