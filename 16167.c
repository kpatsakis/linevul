bool WebPluginProxy::FindProxyForUrl(const GURL& url, std::string* proxy_list) {
  bool result = false;
  Send(new PluginHostMsg_ResolveProxy(route_id_, url, &result, proxy_list));
  return result;
}
