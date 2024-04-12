void RenderProcessHostImpl::RemoveWidget(RenderWidgetHost* widget) {
  RenderWidgetHostImpl* widget_impl =
      static_cast<RenderWidgetHostImpl*>(widget);
  widgets_.erase(widget_impl);

#if defined(OS_ANDROID)
  ChildProcessImportance importance = widget_impl->importance();
  DCHECK(widget_importance_counts_[static_cast<size_t>(importance)]);
  widget_importance_counts_[static_cast<size_t>(importance)]--;
  UpdateProcessPriority();
#endif
}
