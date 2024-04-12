void WebLocalFrameImpl::LoadHTMLString(const WebData& data,
                                       const WebURL& base_url,
                                       const WebURL& unreachable_url,
                                       bool replace) {
  DCHECK(GetFrame());
  CommitDataNavigation(data, WebString::FromUTF8("text/html"),
                       WebString::FromUTF8("UTF-8"), base_url, unreachable_url,
                       replace, WebFrameLoadType::kStandard, WebHistoryItem(),
                       false, nullptr, nullptr, WebNavigationTimings());
}
