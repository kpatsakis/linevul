void FrameFetchContext::SetFirstPartyCookieAndRequestorOrigin(
    ResourceRequest& request) {
  if (request.SiteForCookies().IsNull()) {
    if (request.GetFrameType() == WebURLRequest::kFrameTypeTopLevel) {
      request.SetSiteForCookies(request.Url());
    } else {
      request.SetSiteForCookies(GetSiteForCookies());
    }
  }

  if (!request.RequestorOrigin()) {
    if (request.GetFrameType() == WebURLRequest::kFrameTypeNone) {
      request.SetRequestorOrigin(GetRequestorOrigin());
    } else {
      request.SetRequestorOrigin(GetRequestorOriginForFrameLoading());
    }
  }
}
