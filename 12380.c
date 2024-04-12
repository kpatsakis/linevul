  void WaitForElementVisible(FrameTreeNode* node, const std::string& sel) {
    RunCommandAndWaitForResponse(
        node,
        base::StringPrintf("notifyWhenVisible(document.querySelector('%s'));",
                           sel.c_str()),
        "VISIBLE");
  }
