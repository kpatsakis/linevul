bool SyncTest::ServerSupportsErrorTriggering() const {
  EXPECT_NE(SERVER_TYPE_UNDECIDED, server_type_);

  return server_type_ == LOCAL_PYTHON_SERVER;
}
