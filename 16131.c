RenderWidget* RenderWidget::Create(int32 opener_id,
                                   RenderThreadBase* render_thread,
                                   WebKit::WebPopupType popup_type) {
  DCHECK(opener_id != MSG_ROUTING_NONE);
  scoped_refptr<RenderWidget> widget = new RenderWidget(render_thread,
                                                        popup_type);
  widget->Init(opener_id);  // adds reference
  return widget;
}
