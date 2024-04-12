void Automation::DeleteCookie(const std::string& url,
                              const std::string& cookie_name,
                              Error** error) {
  std::string error_msg;
  if (!SendDeleteCookieJSONRequest(
          automation(), url, cookie_name, &error_msg)) {
    *error = new Error(kUnknownError, error_msg);
  }
}
