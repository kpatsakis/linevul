void InterstitialPageImpl::OnDomOperationResponse(
    RenderFrameHostImpl* source,
    const std::string& json_string) {
  std::string json = json_string;
  NotificationService::current()->Notify(NOTIFICATION_DOM_OPERATION_RESPONSE,
                                         Source<WebContents>(web_contents()),
                                         Details<std::string>(&json));

  if (!enabled())
    return;
  delegate_->CommandReceived(json_string);
}
