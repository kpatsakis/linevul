  void RunTest(const std::string& test_name, const std::string& test_page) {
    OpenDevToolsWindow(test_page);
    std::string result;

    ASSERT_TRUE(
        ui_test_utils::ExecuteJavaScriptAndExtractString(
            client_contents_->render_view_host(),
            L"",
            L"window.domAutomationController.send("
            L"'' + (window.uiTests && (typeof uiTests.runTest)));",
            &result));

    if (result == "function") {
      ASSERT_TRUE(
          ui_test_utils::ExecuteJavaScriptAndExtractString(
              client_contents_->render_view_host(),
              L"",
              UTF8ToWide(StringPrintf("uiTests.runTest('%s')",
                                      test_name.c_str())),
              &result));
      EXPECT_EQ("[OK]", result);
    } else {
      FAIL() << "DevTools front-end is broken.";
    }
    CloseDevToolsWindow();
  }
