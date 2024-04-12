Browser* GetBrowserForDisposition(browser::NavigateParams* params) {
  if (!params->source_contents && params->browser)
    params->source_contents =
        params->browser->GetSelectedTabContentsWrapper();

  Profile* profile =
      params->browser ? params->browser->profile() : params->profile;

  switch (params->disposition) {
    case CURRENT_TAB:
      if (!params->browser && profile) {
        params->browser = Browser::GetOrCreateTabbedBrowser(profile);
      }
      return params->browser;
    case SINGLETON_TAB:
    case NEW_FOREGROUND_TAB:
    case NEW_BACKGROUND_TAB:
      if (params->browser && WindowCanOpenTabs(params->browser))
        return params->browser;
      if (profile)
        return GetOrCreateBrowser(profile);
      return NULL;
    case NEW_POPUP: {
      if (profile) {
        std::string app_name;
        if (!params->extension_app_id.empty()) {
          app_name = web_app::GenerateApplicationNameFromExtensionId(
              params->extension_app_id);
        } else if (params->browser && !params->browser->app_name().empty()) {
          app_name = params->browser->app_name();
        } else if (params->source_contents &&
                   params->source_contents->extension_tab_helper()->is_app()) {
          app_name = web_app::GenerateApplicationNameFromExtensionId(
              params->source_contents->extension_tab_helper()->
                  extension_app()->id());
        }
        if (app_name.empty()) {
          Browser::CreateParams browser_params(Browser::TYPE_POPUP, profile);
          browser_params.initial_bounds = params->window_bounds;
          return Browser::CreateWithParams(browser_params);
        } else {
          return Browser::CreateForApp(Browser::TYPE_POPUP, app_name,
                                       params->window_bounds, profile);
        }
      }
      return NULL;
    }
    case NEW_WINDOW:
      if (profile) {
        Browser* browser = new Browser(Browser::TYPE_TABBED, profile);
        browser->InitBrowserWindow();
        return browser;
      }
      return NULL;
    case OFF_THE_RECORD:
      if (profile)
        return GetOrCreateBrowser(profile->GetOffTheRecordProfile());
      return NULL;
    case SUPPRESS_OPEN:
    case SAVE_TO_DISK:
    case IGNORE_ACTION:
      return NULL;
    default:
      NOTREACHED();
  }
  return NULL;
}
