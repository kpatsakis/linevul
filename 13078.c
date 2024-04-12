ScriptExecutor* ExecuteCodeInTabFunction::GetScriptExecutor(
    std::string* error) {
  Browser* browser = nullptr;
  content::WebContents* contents = nullptr;

  bool success = GetTabById(execute_tab_id_, browser_context(),
                            include_incognito_information(), &browser, nullptr,
                            &contents, nullptr, error) &&
                 contents && browser;

  if (!success)
    return nullptr;

  return TabHelper::FromWebContents(contents)->script_executor();
}
