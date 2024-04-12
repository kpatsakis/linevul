void RenderViewImpl::UpdateScrollState(WebFrame* frame) {
  WebSize offset = frame->scrollOffset();
  WebSize minimum_offset = frame->minimumScrollOffset();
  WebSize maximum_offset = frame->maximumScrollOffset();

  bool is_pinned_to_left = offset.width <= minimum_offset.width;
  bool is_pinned_to_right = offset.width >= maximum_offset.width;

  if (is_pinned_to_left != cached_is_main_frame_pinned_to_left_ ||
      is_pinned_to_right != cached_is_main_frame_pinned_to_right_) {
    Send(new ViewHostMsg_DidChangeScrollOffsetPinningForMainFrame(
          routing_id_, is_pinned_to_left, is_pinned_to_right));

    cached_is_main_frame_pinned_to_left_ = is_pinned_to_left;
    cached_is_main_frame_pinned_to_right_ = is_pinned_to_right;
  }

  Send(new ViewHostMsg_DidChangeScrollOffset(routing_id_));
}
