std::string WebPluginProxy::GetCookies(const GURL& url,
                                       const GURL& first_party_for_cookies) {
  std::string cookies;
  Send(new PluginHostMsg_GetCookies(route_id_, url,
                                    first_party_for_cookies, &cookies));

  return cookies;
}
