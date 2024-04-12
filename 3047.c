  virtual void DoCloseFlushPendingWriteTest(SocketStreamEvent* event) {
    for (size_t i = 0; i < messages_.size(); i++) {
      std::vector<char> frame;
      frame.push_back('\0');
      frame.insert(frame.end(), messages_[i].begin(), messages_[i].end());
      frame.push_back('\xff');
      EXPECT_TRUE(event->socket->SendData(&frame[0], frame.size()));
    }
    event->socket->Close();
  }
