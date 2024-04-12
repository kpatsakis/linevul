void Browser::ConvertContentsToApplication(TabContents* contents) {
  const GURL& url = contents->controller().GetActiveEntry()->url();
  std::string app_name = web_app::GenerateApplicationNameFromURL(url);

  DetachContents(contents);
  Browser* app_browser = Browser::CreateForApp(
      TYPE_POPUP, app_name, gfx::Rect(), profile_);
  TabContentsWrapper* wrapper =
      TabContentsWrapper::GetCurrentWrapperForContents(contents);
  if (!wrapper)
    wrapper = new TabContentsWrapper(contents);
  app_browser->tabstrip_model()->AppendTabContents(wrapper, true);

  contents->GetMutableRendererPrefs()->can_accept_load_drops = false;
  contents->render_view_host()->SyncRendererPrefs();
  app_browser->window()->Show();
}
