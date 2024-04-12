ChromeContentBrowserClient::CreateLoginDelegate(
    net::AuthChallengeInfo* auth_info,
    content::WebContents* web_contents,
    const content::GlobalRequestID& request_id,
    bool is_request_for_main_frame,
    const GURL& url,
    scoped_refptr<net::HttpResponseHeaders> response_headers,
    bool first_auth_attempt,
    LoginAuthRequiredCallback auth_required_callback) {
  return CreateLoginPrompt(
      auth_info, web_contents, request_id, is_request_for_main_frame, url,
      std::move(response_headers), std::move(auth_required_callback));
}
