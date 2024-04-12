void RenderViewImpl::OnSelectWordAroundCaret() {
  bool did_select = false;
  int start_adjust = 0;
  int end_adjust = 0;

  if (webview()) {
    WebLocalFrame* focused_frame = GetWebView()->FocusedFrame();
    if (focused_frame) {
      input_handler_->set_handling_input_event(true);
      blink::WebRange initial_range = focused_frame->SelectionRange();
      if (!initial_range.IsNull())
        did_select = focused_frame->SelectWordAroundCaret();
      if (did_select) {
        blink::WebRange adjusted_range = focused_frame->SelectionRange();
        start_adjust =
            adjusted_range.StartOffset() - initial_range.StartOffset();
        end_adjust = adjusted_range.EndOffset() - initial_range.EndOffset();
      }
      input_handler_->set_handling_input_event(false);
    }
  }
  Send(new ViewHostMsg_SelectWordAroundCaretAck(GetRoutingID(), did_select,
                                                start_adjust, end_adjust));
}
