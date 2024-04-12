void WebContentsImpl::OnDomOperationResponse(RenderFrameHostImpl* source,
                                             const std::string& json_string) {
  std::string json = json_string;
  NotificationService::current()->Notify(NOTIFICATION_DOM_OPERATION_RESPONSE,
                                         Source<WebContents>(this),
                                         Details<std::string>(&json));
}
