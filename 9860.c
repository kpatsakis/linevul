void TabsDetectLanguageFunction::GotLanguage(const std::string& language) {
  Respond(OneArgument(std::make_unique<base::Value>(language)));

  Release();  // Balanced in Run()
}
