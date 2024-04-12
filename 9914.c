void WebFrameLoaderClient::dispatchWillSendRequest(
    DocumentLoader* loader, unsigned long identifier, ResourceRequest& request,
    const ResourceResponse& redirect_response) {

  if (loader) {
    request.setTargetType(DetermineTargetTypeFromLoader(loader));
  }

  if (request.url().isEmpty())
    request.setURL(KURL(ParsedURLString, "about:blank"));
  if (request.firstPartyForCookies().isEmpty())
    request.setFirstPartyForCookies(KURL(ParsedURLString, "about:blank"));

  if (webframe_->client()) {
    WrappedResourceRequest webreq(request);
    WrappedResourceResponse webresp(redirect_response);
    webframe_->client()->willSendRequest(
        webframe_, identifier, webreq, webresp);
  }
}
