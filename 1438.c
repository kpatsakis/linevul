  void FocusFirstNameField() {
    LOG(WARNING) << "Clicking on the tab.";
    content::SimulateMouseClick(
        browser()->tab_strip_model()->GetActiveWebContents(),
        0,
        WebKit::WebMouseEvent::ButtonLeft);

    LOG(WARNING) << "Focusing the first name field.";
    bool result = false;
    ASSERT_TRUE(content::ExecuteScriptAndExtractBool(
        render_view_host(),
        "if (document.readyState === 'complete')"
        "  document.getElementById('firstname').focus();"
        "else"
        "  domAutomationController.send(false);",
        &result));
    ASSERT_TRUE(result);
  }
