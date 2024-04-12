int GetReceivedMessages(FrameTreeNode* ftn) {
  int received_messages = 0;
  EXPECT_TRUE(ExecuteScriptAndExtractInt(
      ftn, "window.domAutomationController.send(window.receivedMessages);",
      &received_messages));
  return received_messages;
}
