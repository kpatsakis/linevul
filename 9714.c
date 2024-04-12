bool DocumentLoader::RedirectReceived(
    Resource* resource,
    const ResourceRequest& request,
    const ResourceResponse& redirect_response) {
  DCHECK(frame_);
  DCHECK_EQ(resource, GetResource());
  DCHECK(!redirect_response.IsNull());
  request_ = request;

  const KURL& request_url = request_.Url();
  scoped_refptr<const SecurityOrigin> redirecting_origin =
      SecurityOrigin::Create(redirect_response.Url());
  if (!redirecting_origin->CanDisplay(request_url)) {
    frame_->Console().AddMessage(ConsoleMessage::Create(
        kSecurityMessageSource, kErrorMessageLevel,
        "Not allowed to load local resource: " + request_url.GetString()));
    fetcher_->StopFetching();
    return false;
  }

  DCHECK(!GetTiming().FetchStart().is_null());
  AppendRedirect(request_url);
  GetTiming().AddRedirect(redirect_response.Url(), request_url);

  history_item_.Clear();

  return true;
}
