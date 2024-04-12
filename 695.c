  void TestPDFNavigationFromFrame(
      const std::string& javascript,
      ExpectedNavigationStatus expected_navigation_status) {
    RenderFrameHost* child =
        ChildFrameAt(shell()->web_contents()->GetMainFrame(), 0);
    ASSERT_TRUE(child);
    if (AreAllSitesIsolatedForTesting()) {
      ASSERT_TRUE(child->IsCrossProcessSubframe());
    }
    ExecuteScriptAndCheckPDFNavigation(child, javascript,
                                       expected_navigation_status);
  }
