  bool GetInputText(std::string* input_text) {
    return ExecuteScriptAndExtractString(interstitial_->GetMainFrame(),
                                         "get_input_text()", input_text);
  }
