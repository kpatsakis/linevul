WebViewTestClient::WebViewTestClient(
    WebViewTestProxyBase* web_view_test_proxy_base)
    : web_view_test_proxy_base_(web_view_test_proxy_base) {
  DCHECK(web_view_test_proxy_base);
}
