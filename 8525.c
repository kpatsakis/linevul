void ContentSecurityPolicy::ReportInvalidSourceExpression(
    const String& directive_name,
    const String& source) {
  String message = "The source list for Content Security Policy directive '" +
                   directive_name + "' contains an invalid source: '" + source +
                   "'. It will be ignored.";
  if (EqualIgnoringASCIICase(source, "'none'"))
    message = message +
              " Note that 'none' has no effect unless it is the only "
              "expression in the source list.";
  LogToConsole(message);
}
