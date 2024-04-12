ExtensionFunction::ResponseAction WindowsGetFunction::Run() {
  std::unique_ptr<windows::Get::Params> params(
      windows::Get::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());

  ApiParameterExtractor<windows::Get::Params> extractor(params.get());
  Browser* browser = nullptr;
  std::string error;
  if (!windows_util::GetBrowserFromWindowID(this, params->window_id,
                                            extractor.type_filters(), &browser,
                                            &error)) {
    return RespondNow(Error(error));
  }

  ExtensionTabUtil::PopulateTabBehavior populate_tab_behavior =
      extractor.populate_tabs() ? ExtensionTabUtil::kPopulateTabs
                                : ExtensionTabUtil::kDontPopulateTabs;
  std::unique_ptr<base::DictionaryValue> windows =
      ExtensionTabUtil::CreateWindowValueForExtension(*browser, extension(),
                                                      populate_tab_behavior);
  return RespondNow(OneArgument(std::move(windows)));
}
