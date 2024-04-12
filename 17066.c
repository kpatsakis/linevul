mojom::WidgetInputHandler* RenderWidgetHostImpl::GetWidgetInputHandler() {
  if (associated_widget_input_handler_)
    return associated_widget_input_handler_.get();
  if (widget_input_handler_)
    return widget_input_handler_.get();
  return legacy_widget_input_handler_.get();
}
