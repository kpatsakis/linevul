std::string ReadSubresourceFromRenderer(Browser* browser,
                                        const GURL& url,
                                        bool asynchronous_xhr = true) {
  static const char asynchronous_script[] = R"((url => {
    var xhr = new XMLHttpRequest();
    xhr.open('GET', url, true);
    xhr.onload = () => domAutomationController.send(xhr.responseText);
    xhr.send();
  }))";
  static const char synchronous_script[] = R"((url => {
    var xhr = new XMLHttpRequest();
    xhr.open('GET', url, false);
    xhr.send();
    domAutomationController.send(xhr.responseText);
  }))";
  std::string result;
  EXPECT_TRUE(ExecuteScriptAndExtractString(
      browser->tab_strip_model()->GetActiveWebContents(),
      base::StrCat({asynchronous_xhr ? asynchronous_script : synchronous_script,
                    "('", url.spec(), "')"}),
      &result));
  return result;
}
