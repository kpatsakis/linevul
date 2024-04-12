void AppendMatchingCookiesToList(
    net::CookieStore* cookie_store, const std::string& store_id,
    const GURL& url, const DictionaryValue* details,
    const Extension* extension,
    ListValue* match_list) {
  net::CookieMonster::CookieList all_cookies = GetCookieListFromStore(
      cookie_store, url);
  net::CookieMonster::CookieList::const_iterator it;
  for (it = all_cookies.begin(); it != all_cookies.end(); ++it) {
    GURL cookie_domain_url = GetURLFromCookiePair(*it);
    if (!extension->HasHostPermission(cookie_domain_url))
      continue;
    extension_cookies_helpers::MatchFilter filter(details);
    if (filter.MatchesCookie(*it))
      match_list->Append(CreateCookieValue(*it, store_id));
  }
}
