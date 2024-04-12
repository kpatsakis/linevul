void RenderWidget::OnMsgRepaint(const gfx::Size& size_to_paint) {
  if (!webwidget_)
    return;

  set_next_paint_is_repaint_ack();
  gfx::Rect repaint_rect(size_to_paint.width(), size_to_paint.height());
  didInvalidateRect(repaint_rect);
}
