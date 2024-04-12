  std::string GetOrientationType() {
    std::string type;
    ExecuteScriptAndGetValue(shell()->web_contents()->GetMainFrame(),
                             "screen.orientation.type")->GetAsString(&type);
    return type;
  }
