std::string WebPluginImpl::GetCookies(const GURL& url,
                                      const GURL& first_party_for_cookies) {
  return UTF16ToUTF8(WebKit::webKitClient()->cookies(url,
                                                     first_party_for_cookies));
}
