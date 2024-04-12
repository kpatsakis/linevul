void ExtensionBrowserTest::NavigateInRenderer(content::WebContents* contents,
                                              const GURL& url) {
  content::WaitForLoadStop(contents);
  bool result = false;
  content::WindowedNotificationObserver windowed_observer(
      content::NOTIFICATION_LOAD_STOP,
      content::NotificationService::AllSources());
  ASSERT_TRUE(content::ExecuteScriptAndExtractBool(
      contents,
      "window.addEventListener('unload', function() {"
      "    window.domAutomationController.send(true);"
      "}, false);"
      "window.location = '" + url.spec() + "';",
      &result));
  ASSERT_TRUE(result);
  windowed_observer.Wait();
  EXPECT_EQ(url, contents->GetController().GetLastCommittedEntry()->GetURL());
}
