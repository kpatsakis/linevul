  bool WindowOrientationSupported() {
    bool support;
    ExecuteScriptAndGetValue(shell()->web_contents()->GetMainFrame(),
                             "'orientation' in window")->GetAsBoolean(&support);
    return support;
  }
