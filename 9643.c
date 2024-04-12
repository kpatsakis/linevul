void RenderWidget::didChangeCursor(const WebCursorInfo& cursor_info) {
  WebCursor cursor(cursor_info);

  if (!current_cursor_.IsEqual(cursor)) {
    current_cursor_ = cursor;
    Send(new ViewHostMsg_SetCursor(routing_id_, cursor));
  }
}
