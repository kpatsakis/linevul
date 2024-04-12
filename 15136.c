Browser* InProcessBrowserTest::CreateBrowser(Profile* profile) {
  Browser* browser = new Browser(
      Browser::CreateParams(profile, chrome::GetActiveDesktop()));
  AddBlankTabAndShow(browser);
  return browser;
}
