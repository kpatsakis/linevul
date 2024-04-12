void Browser::OpenBookmarkManagerWindow(Profile* profile) {
  Browser* browser = Browser::Create(profile);
  browser->OpenBookmarkManager();
  browser->window()->Show();
}
