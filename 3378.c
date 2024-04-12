DevToolsWindow* DevToolsWindow::Create(
    Profile* profile,
    const GURL& frontend_url,
    content::WebContents* inspected_web_contents,
    bool shared_worker_frontend,
    bool v8_only_frontend,
    const std::string& remote_frontend,
    bool can_dock,
    const std::string& settings) {
  if (profile->GetPrefs()->GetBoolean(prefs::kDevToolsDisabled) ||
      base::CommandLine::ForCurrentProcess()->HasSwitch(switches::kKioskMode))
    return nullptr;

  if (inspected_web_contents) {
    Browser* browser = NULL;
    int tab;
    if (!FindInspectedBrowserAndTabIndex(inspected_web_contents,
                                         &browser, &tab) ||
        browser->is_type_popup()) {
      can_dock = false;
    }
  }

  GURL url(GetDevToolsURL(profile, frontend_url,
                          shared_worker_frontend,
                          v8_only_frontend,
                          remote_frontend,
                          can_dock));
  std::unique_ptr<WebContents> main_web_contents(
      WebContents::Create(WebContents::CreateParams(profile)));
  main_web_contents->GetController().LoadURL(
      DecorateFrontendURL(url), content::Referrer(),
      ui::PAGE_TRANSITION_AUTO_TOPLEVEL, std::string());
  DevToolsUIBindings* bindings =
      DevToolsUIBindings::ForWebContents(main_web_contents.get());
  if (!bindings)
    return nullptr;
  if (!settings.empty())
    SetPreferencesFromJson(profile, settings);
  return new DevToolsWindow(profile, main_web_contents.release(), bindings,
                            inspected_web_contents, can_dock);
}
