BrowserLauncherItemController* BrowserLauncherItemController::Create(
    Browser* browser) {
  if (!ChromeLauncherController::instance())
    return NULL;

  Type type;
  std::string app_id;
  if (browser->is_type_tabbed() || browser->is_type_popup()) {
    type = TYPE_TABBED;
  } else if (browser->is_app()) {
    if (browser->is_type_panel()) {
      if (browser->app_type() == Browser::APP_TYPE_CHILD)
        type = TYPE_EXTENSION_PANEL;
      else
        type = TYPE_APP_PANEL;
    } else {
      type = TYPE_TABBED;
    }
    app_id = web_app::GetExtensionIdFromApplicationName(browser->app_name());
  } else {
    return NULL;
  }
  BrowserLauncherItemController* controller =
      new BrowserLauncherItemController(type,
                                        browser->window()->GetNativeWindow(),
                                        browser->tab_strip_model(),
                                        ChromeLauncherController::instance(),
                                        app_id);
  controller->Init();
  return controller;
}
