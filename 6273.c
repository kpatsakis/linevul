RenderWidgetHostViewAura* ToRenderWidgetHostViewAura(
    RenderWidgetHostView* view) {
  if (!view || RenderViewHostFactory::has_factory())
    return NULL;  // Can't cast to RenderWidgetHostViewAura in unit tests.
  RenderProcessHostImpl* process = static_cast<RenderProcessHostImpl*>(
      view->GetRenderWidgetHost()->GetProcess());
  if (process->IsGuest())
    return NULL;
  return static_cast<RenderWidgetHostViewAura*>(view);
}
