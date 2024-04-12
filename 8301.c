void RenderFrameImpl::DidStopLoading() {
  TRACE_EVENT1("navigation,rail", "RenderFrameImpl::didStopLoading",
               "id", routing_id_);

  history_subframe_unique_names_.clear();

  blink::WebIconURL::Type icon_types_mask =
      static_cast<blink::WebIconURL::Type>(
          blink::WebIconURL::kTypeFavicon |
          blink::WebIconURL::kTypeTouchPrecomposed |
          blink::WebIconURL::kTypeTouch);
  SendUpdateFaviconURL(icon_types_mask);

  render_view_->FrameDidStopLoading(frame_);
  Send(new FrameHostMsg_DidStopLoading(routing_id_));
}
