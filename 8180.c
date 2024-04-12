void WebPluginImpl::SetReferrer(WebKit::WebURLRequest* request,
                                Referrer referrer_flag) {
  switch (referrer_flag) {
    case DOCUMENT_URL:
      webframe_->setReferrerForRequest(*request, GURL());
      break;

    case PLUGIN_SRC:
      webframe_->setReferrerForRequest(*request, plugin_url_);
      break;

    default:
      break;
  }
}
