void WebContentsImpl::FocusedNodeTouched(bool editable) {
#if defined(OS_WIN)
  RenderWidgetHostView* view = GetRenderWidgetHostView();
  if (!view)
    return;
  view->FocusedNodeTouched(editable);
#endif
}
