TabContents* Browser::OpenAppShortcutWindow(Profile* profile,
                                            const GURL& url,
                                            bool update_shortcut) {
  Browser* app_browser;
  TabContents* tab = OpenApplicationWindow(
      profile,
      NULL,  // this is a URL app.  No extension.
      extension_misc::LAUNCH_WINDOW,
      url,
      &app_browser);

  if (!tab)
    return NULL;

  if (update_shortcut) {
    app_browser->pending_web_app_action_ = UPDATE_SHORTCUT;
  }
  return tab;
}
