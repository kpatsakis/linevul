  void SetCookieCallback(bool result) {
    ASSERT_TRUE(result);
    quit_closure_.Run();
  }
