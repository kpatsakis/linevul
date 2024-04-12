void ContentSecurityPolicy::reportUnsupportedDirective(const String& name) {
  static const char allow[] = "allow";
  static const char options[] = "options";
  static const char policyURI[] = "policy-uri";
  static const char allowMessage[] =
      "The 'allow' directive has been replaced with 'default-src'. Please use "
      "that directive instead, as 'allow' has no effect.";
  static const char optionsMessage[] =
      "The 'options' directive has been replaced with 'unsafe-inline' and "
      "'unsafe-eval' source expressions for the 'script-src' and 'style-src' "
      "directives. Please use those directives instead, as 'options' has no "
      "effect.";
  static const char policyURIMessage[] =
      "The 'policy-uri' directive has been removed from the "
      "specification. Please specify a complete policy via "
      "the Content-Security-Policy header.";

  String message =
      "Unrecognized Content-Security-Policy directive '" + name + "'.\n";
  MessageLevel level = ErrorMessageLevel;
  if (equalIgnoringCase(name, allow)) {
    message = allowMessage;
  } else if (equalIgnoringCase(name, options)) {
    message = optionsMessage;
  } else if (equalIgnoringCase(name, policyURI)) {
    message = policyURIMessage;
  } else if (getDirectiveType(name) != DirectiveType::Undefined) {
    message = "The Content-Security-Policy directive '" + name +
              "' is implemented behind a flag which is currently disabled.\n";
    level = InfoMessageLevel;
  }

  logToConsole(message, level);
}
