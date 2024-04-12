bool RenderWidgetHostViewAndroid::IsShowing() {
  return is_layer_attached_ && content_view_core_;
}
