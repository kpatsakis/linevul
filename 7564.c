bool DocumentLoader::RedirectReceived(
    Resource* resource,
    const ResourceRequest& request,
    const ResourceResponse& redirect_response) {
  DCHECK(frame_);
  DCHECK_EQ(resource, main_resource_);
  DCHECK(!redirect_response.IsNull());
  request_ = request;

  const KURL& request_url = request_.Url();
  RefPtr<SecurityOrigin> redirecting_origin =
      SecurityOrigin::Create(redirect_response.Url());
  if (!redirecting_origin->CanDisplay(request_url)) {
    frame_->Console().AddMessage(ConsoleMessage::Create(
        kSecurityMessageSource, kErrorMessageLevel,
        "Not allowed to load local resource: " + request_url.GetString()));
    fetcher_->StopFetching();
    return false;
  }
  if (GetFrameLoader().ShouldContinueForRedirectNavigationPolicy(
          request_, SubstituteData(), this, kCheckContentSecurityPolicy,
          navigation_type_, kNavigationPolicyCurrentTab, load_type_,
          IsClientRedirect(), nullptr) != kNavigationPolicyCurrentTab) {
    fetcher_->StopFetching();
    return false;
  }

  DCHECK(GetTiming().FetchStart());
  AppendRedirect(request_url);
  GetTiming().AddRedirect(redirect_response.Url(), request_url);

  history_item_.Clear();

  GetLocalFrameClient().DispatchDidReceiveServerRedirectForProvisionalLoad();

  return true;
}
