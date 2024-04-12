void FillNavigationParamsRequest(
    const CommonNavigationParams& common_params,
    const CommitNavigationParams& commit_params,
    blink::WebNavigationParams* navigation_params) {
  navigation_params->url = !commit_params.original_url.is_empty()
                               ? commit_params.original_url
                               : common_params.url;
  navigation_params->http_method = WebString::FromLatin1(
      !commit_params.original_method.empty() ? commit_params.original_method
                                             : common_params.method);

  if (common_params.referrer.url.is_valid()) {
    WebString referrer = WebSecurityPolicy::GenerateReferrerHeader(
        common_params.referrer.policy, common_params.url,
        WebString::FromUTF8(common_params.referrer.url.spec()));
    navigation_params->referrer = referrer;
    navigation_params->referrer_policy = common_params.referrer.policy;
  }
  if (common_params.referrer.policy !=
      network::mojom::ReferrerPolicy::kDefault) {
    navigation_params->referrer_policy = common_params.referrer.policy;
  }

  if (common_params.post_data) {
    navigation_params->http_body =
        GetWebHTTPBodyForRequestBody(*common_params.post_data);
    if (!commit_params.post_content_type.empty()) {
      navigation_params->http_content_type =
          WebString::FromASCII(commit_params.post_content_type);
    }
  }

  navigation_params->previews_state =
      static_cast<WebURLRequest::PreviewsState>(common_params.previews_state);
  navigation_params->origin_policy =
      WebString::FromUTF8(common_params.origin_policy);

  if (common_params.initiator_origin) {
    navigation_params->requestor_origin =
        common_params.initiator_origin.value();
  }

  navigation_params->was_discarded = commit_params.was_discarded;
#if defined(OS_ANDROID)
  navigation_params->had_transient_activation = common_params.has_user_gesture;
#endif
}
