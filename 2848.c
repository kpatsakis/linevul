ExtensionFunction::ResponseAction TabsGetSelectedFunction::Run() {
  int window_id = extension_misc::kCurrentWindowId;

  std::unique_ptr<tabs::GetSelected::Params> params(
      tabs::GetSelected::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());
  if (params->window_id.get())
    window_id = *params->window_id;

  Browser* browser = NULL;
  std::string error;
  if (!GetBrowserFromWindowID(this, window_id, &browser, &error))
    return RespondNow(Error(error));

  TabStripModel* tab_strip = browser->tab_strip_model();
  WebContents* contents = tab_strip->GetActiveWebContents();
  if (!contents)
    return RespondNow(Error(keys::kNoSelectedTabError));
  return RespondNow(ArgumentList(
      tabs::Get::Results::Create(*ExtensionTabUtil::CreateTabObject(
          contents, ExtensionTabUtil::kScrubTab, extension(), tab_strip,
          tab_strip->active_index()))));
}
