 GURL GetURLFromCookiePair(
    const net::CookieMonster::CookieListPair& cookie_pair) {
  const std::string& domain_key = cookie_pair.first;
  const net::CookieMonster::CanonicalCookie& cookie = cookie_pair.second;
  const std::string scheme =
      cookie.IsSecure() ? chrome::kHttpsScheme : chrome::kHttpScheme;
  const std::string host =
      domain_key.find('.') != 0 ? domain_key : domain_key.substr(1);
  return GURL(scheme + chrome::kStandardSchemeSeparator + host + "/");
}
