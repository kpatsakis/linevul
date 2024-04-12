void ContentSecurityPolicy::ReportValueForEmptyDirective(const String& name,
                                                         const String& value) {
  LogToConsole("The Content Security Policy directive '" + name +
               "' should be empty, but was delivered with a value of '" +
               value +
               "'. The directive has been applied, and the value ignored.");
}
