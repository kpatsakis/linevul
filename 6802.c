  void RunTests(const std::string& extension_dirname) {
    ExtensionTestMessageListener listener("PASS", true);
    LaunchTestingApp(extension_dirname);
    EXPECT_TRUE(listener.WaitUntilSatisfied());
  }
