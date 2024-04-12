  void ExpectDelegateCreation() {
    delegate_ = new StrictMock<MockDelegate>();
    mock_delegate_factory_.PrepareDelegateForCreation(
        base::WrapUnique(delegate_));
    EXPECT_TRUE(
        base::CancelableSyncSocket::CreatePair(&local_, foreign_socket_.get()));
    EXPECT_TRUE(mem_.CreateAnonymous(kShmemSize));
    EXPECT_CALL(mock_delegate_factory_, MockCreateDelegate(NotNull()))
        .WillOnce(SaveArg<0>(&delegate_event_handler_));
  }
