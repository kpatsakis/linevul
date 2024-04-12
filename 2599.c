  std::string GetBody(Browser* browser) {
    std::string body;
    EXPECT_TRUE(content::ExecuteScriptAndExtractString(
        browser->tab_strip_model()->GetActiveWebContents(),
        "window.domAutomationController.send(document.body.textContent);",
        &body));
    return body;
  }
