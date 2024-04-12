void RenderFrameImpl::PostMessageEvent(int32_t source_routing_id,
                                       const base::string16& source_origin,
                                       const base::string16& target_origin,
                                       blink::TransferableMessage message) {
  message.EnsureDataIsOwned();

  WebFrame* source_frame = nullptr;
  if (source_routing_id != MSG_ROUTING_NONE) {
    RenderFrameProxy* source_proxy =
        RenderFrameProxy::FromRoutingID(source_routing_id);
    if (source_proxy)
      source_frame = source_proxy->web_frame();
  }

  WebSecurityOrigin target_security_origin;
  if (!target_origin.empty()) {
    target_security_origin = WebSecurityOrigin::CreateFromString(
        WebString::FromUTF16(target_origin));
  }

  WebDOMMessageEvent msg_event(std::move(message),
                               WebString::FromUTF16(source_origin),
                               source_frame, frame_->GetDocument());

  frame_->DispatchMessageEventWithOriginCheck(target_security_origin, msg_event,
                                              message.has_user_gesture);
}
