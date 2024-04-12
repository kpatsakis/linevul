void ChromeContentBrowserClient::GetSchemesBypassingSecureContextCheckWhitelist(
    std::set<std::string>* schemes) {
  *schemes = secure_origin_whitelist::GetSchemesBypassingSecureContextCheck();
}
