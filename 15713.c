Browser* Browser::Create(Profile* profile) {
  Browser* browser = new Browser(TYPE_TABBED, profile);
  browser->InitBrowserWindow();
  return browser;
}
