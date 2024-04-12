void InspectorPageAgent::DidClearDocumentOfWindowObject(LocalFrame* frame) {
  if (!GetFrontend())
    return;

  protocol::DictionaryValue* scripts =
      state_->getObject(PageAgentState::kPageAgentScriptsToEvaluateOnLoad);
  if (scripts) {
    for (size_t i = 0; i < scripts->size(); ++i) {
      auto script = scripts->at(i);
      String script_text;
      if (script.second->asString(&script_text))
        frame->GetScriptController().ExecuteScriptInMainWorld(script_text);
    }
  }
  if (!script_to_evaluate_on_load_once_.IsEmpty()) {
    frame->GetScriptController().ExecuteScriptInMainWorld(
        script_to_evaluate_on_load_once_);
  }
}
