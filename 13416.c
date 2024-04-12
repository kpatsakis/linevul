void ResourceMessageFilter::OnGetCookies(const GURL& url,
                                         const GURL& first_party_for_cookies,
                                         IPC::Message* reply_msg) {
  URLRequestContext* context = GetRequestContextForURL(url);

  GetCookiesCompletion* callback =
      new GetCookiesCompletion(url, reply_msg, this, context);

  int policy = net::OK;
  if (context->cookie_policy()) {
    policy = context->cookie_policy()->CanGetCookies(
        url, first_party_for_cookies, callback);
    if (policy == net::ERR_IO_PENDING) {
      Send(new ViewMsg_SignalCookiePromptEvent());
      return;
    }
  }
  callback->Run(policy);
}
