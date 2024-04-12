void RenderFrameImpl::LoadDataURL(
    const CommonNavigationParams& params,
    const RequestNavigationParams& request_params,
    WebLocalFrame* frame,
    blink::WebFrameLoadType load_type,
    blink::WebHistoryItem item_for_history_navigation,
    blink::WebHistoryLoadType history_load_type,
    bool is_client_redirect) {
  GURL data_url = params.url;
#if defined(OS_ANDROID)
  if (!request_params.data_url_as_string.empty()) {
#if DCHECK_IS_ON()
    {
      std::string mime_type, charset, data;
      DCHECK(net::DataURL::Parse(data_url, &mime_type, &charset, &data));
      DCHECK(data.empty());
    }
#endif
    data_url = GURL(request_params.data_url_as_string);
    if (!data_url.is_valid() || !data_url.SchemeIs(url::kDataScheme)) {
      data_url = params.url;
    }
  }
#endif
  std::string mime_type, charset, data;
  if (net::DataURL::Parse(data_url, &mime_type, &charset, &data)) {
    const GURL base_url = params.base_url_for_data_url.is_empty() ?
        params.url : params.base_url_for_data_url;
    bool replace = load_type == WebFrameLoadType::kReloadBypassingCache ||
                   load_type == WebFrameLoadType::kReload;

    frame->LoadData(
        WebData(data.c_str(), data.length()), WebString::FromUTF8(mime_type),
        WebString::FromUTF8(charset), base_url,
        params.history_url_for_data_url, replace, load_type,
        item_for_history_navigation, history_load_type, is_client_redirect);
  } else {
    CHECK(false) << "Invalid URL passed: "
                 << params.url.possibly_invalid_spec();
  }
}
