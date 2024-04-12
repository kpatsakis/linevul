  void NavigateFrameAndWait(FrameTreeNode* node, const GURL& url) {
    NavigateFrameToURL(node, url);
    EXPECT_TRUE(WaitForLoadStop(shell()->web_contents()));
    EXPECT_EQ(url, node->current_url());
  }
