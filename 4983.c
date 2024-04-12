  void Fail() {
    if (!expect_fail_)
      FAIL();
    QuitMessageLoop();
  }
