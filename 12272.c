static void WindowOpenHelper(Browser* browser, const GURL& start_url,
                             const std::string& newtab_url,
                             TabContents** newtab_result) {
  ui_test_utils::NavigateToURL(browser, start_url);

  ASSERT_TRUE(ui_test_utils::ExecuteJavaScript(
      browser->GetSelectedTabContents()->render_view_host(), L"",
      L"window.open('" + UTF8ToWide(newtab_url) + L"');"));

  Browser* last_active_browser = BrowserList::GetLastActive();
  EXPECT_TRUE(last_active_browser);
  TabContents* newtab = last_active_browser->GetSelectedTabContents();
  EXPECT_TRUE(newtab);
  GURL expected_url = start_url.Resolve(newtab_url);
  if (!newtab->controller().GetLastCommittedEntry() ||
      newtab->controller().GetLastCommittedEntry()->url() != expected_url)
    ui_test_utils::WaitForNavigation(&newtab->controller());
  EXPECT_EQ(expected_url,
            newtab->controller().GetLastCommittedEntry()->url());
  if (newtab_result)
    *newtab_result = newtab;
}
