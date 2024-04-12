  void ReadFromSocketWithPort(uint16_t port) {
    EXPECT_TRUE(base::Contains(sockets_, port));
    sockets_[port] = SocketStatus::kReadFrom;
    first_read_loop_.Quit();
  }
