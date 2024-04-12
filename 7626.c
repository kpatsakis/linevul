void WaitForExtensionsDevModeControlsVisibility(
    content::WebContents* contents,
    const char* dev_controls_accessor_js,
    const char* dev_controls_visibility_check_js,
    bool expected_visible) {
  bool done = false;
  ASSERT_TRUE(content::ExecuteScriptAndExtractBool(
      contents,
      base::StringPrintf(
          "var screenElement = %s;"
          "function SendReplyIfAsExpected() {"
          "  var is_visible = %s;"
          "  if (is_visible != %s)"
          "    return false;"
          "  observer.disconnect();"
          "  domAutomationController.send(true);"
          "  return true;"
          "}"
          "var observer = new MutationObserver(SendReplyIfAsExpected);"
          "if (!SendReplyIfAsExpected()) {"
          "  var options = { 'attributes': true };"
          "  observer.observe(screenElement, options);"
          "}",
          dev_controls_accessor_js,
          dev_controls_visibility_check_js,
          (expected_visible ? "true" : "false")),
      &done));
}
