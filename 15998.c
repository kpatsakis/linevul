ExtensionFunction::ResponseAction InputImeCommitTextFunction::Run() {
  InputImeEventRouter* event_router =
      GetInputImeEventRouter(Profile::FromBrowserContext(browser_context()));
  InputMethodEngineBase* engine =
      event_router ? event_router->GetActiveEngine(extension_id()) : nullptr;
  if (engine) {
    std::unique_ptr<CommitText::Params> parent_params(
        CommitText::Params::Create(*args_));
    const CommitText::Params::Parameters& params = parent_params->parameters;
    std::string error;
    if (!engine->CommitText(params.context_id, params.text.c_str(), &error)) {
      std::unique_ptr<base::ListValue> results =
          std::make_unique<base::ListValue>();
      results->Append(std::make_unique<base::Value>(false));
      return RespondNow(ErrorWithArguments(std::move(results), error));
    }
  }
  return RespondNow(OneArgument(std::make_unique<base::Value>(true)));
}
