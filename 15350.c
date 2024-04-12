  GetRawCookiesCompletion(const GURL& url, IPC::Message* reply_msg,
                          ResourceMessageFilter* filter,
                          URLRequestContext* context)
      : url_(url),
        reply_msg_(reply_msg),
        filter_(filter),
        context_(context) {
  }
