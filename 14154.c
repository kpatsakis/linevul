void WebFrameLoaderClient::dispatchDidReceiveServerRedirectForProvisionalLoad() {
  WebDataSourceImpl* ds = webframe_->GetProvisionalDataSourceImpl();
  if (!ds) {
    NOTREACHED() << "Got a server redirect when there is no provisional DS";
    return;
  }

  if (ds->request().isNull())
    return;

  DCHECK(ds->hasRedirectChain());

  ds->appendRedirect(ds->request().url());

  if (webframe_->client())
    webframe_->client()->didReceiveServerRedirectForProvisionalLoad(webframe_);
}
