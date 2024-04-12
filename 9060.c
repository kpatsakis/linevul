  void JSEval(const std::string& script) {
    EXPECT_TRUE(content::ExecuteScript(
        browser()->tab_strip_model()->GetActiveWebContents(), script));
  }
