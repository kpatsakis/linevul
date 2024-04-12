void DocumentLoader::CancelLoadAfterCSPDenied(
    const ResourceResponse& response) {
  probe::didReceiveResourceResponse(frame_->GetDocument(),
                                    MainResourceIdentifier(), this, response,
                                    GetResource());

  SetWasBlockedAfterCSP();

  ClearResource();
  content_security_policy_.Clear();
  KURL blocked_url = SecurityOrigin::UrlWithUniqueOpaqueOrigin();
  original_request_.SetURL(blocked_url);
  request_.SetURL(blocked_url);
  redirect_chain_.pop_back();
  AppendRedirect(blocked_url);
  response_ = ResourceResponse(blocked_url);
  response_.SetMimeType("text/html");
  FinishedLoading(CurrentTimeTicks());

  return;
}
