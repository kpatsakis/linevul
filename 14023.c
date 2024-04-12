  void ExecuteScriptAndCheckPDFNavigation(
      RenderFrameHost* rfh,
      const std::string& javascript,
      ExpectedNavigationStatus expected_navigation_status) {
    const GURL original_url(shell()->web_contents()->GetLastCommittedURL());

    const std::string expected_message =
        (expected_navigation_status == NAVIGATION_ALLOWED)
            ? std::string()
            : kDataUrlBlockedPattern;

    std::unique_ptr<ConsoleObserverDelegate> console_delegate;
    if (!expected_message.empty()) {
      console_delegate.reset(new ConsoleObserverDelegate(
          shell()->web_contents(), expected_message));
      shell()->web_contents()->SetDelegate(console_delegate.get());
    }

    TestNavigationObserver navigation_observer(shell()->web_contents());
    EXPECT_TRUE(ExecuteScript(rfh, javascript));

    if (console_delegate) {
      console_delegate->Wait();
      shell()->web_contents()->SetDelegate(nullptr);
    }

    switch (expected_navigation_status) {
      case NAVIGATION_ALLOWED:
        navigation_observer.Wait();
        EXPECT_TRUE(shell()->web_contents()->GetLastCommittedURL().SchemeIs(
            url::kDataScheme));
        EXPECT_TRUE(navigation_observer.last_navigation_url().SchemeIs(
            url::kDataScheme));
        EXPECT_TRUE(navigation_observer.last_navigation_succeeded());
        break;

      case NAVIGATION_BLOCKED:
        EXPECT_EQ(original_url, shell()->web_contents()->GetLastCommittedURL());
        EXPECT_FALSE(navigation_observer.last_navigation_succeeded());
        break;

      default:
        NOTREACHED();
    }
  }
