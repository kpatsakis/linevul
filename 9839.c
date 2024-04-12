void WebGLRenderingContextBase::RestoreEvictedContext(
    WebGLRenderingContextBase* context) {
  DCHECK(!ForciblyEvictedContexts().Contains(context));
  DCHECK(!ActiveContexts().Contains(context));

  unsigned max_gl_contexts = CurrentMaxGLContexts();
  while (ActiveContexts().size() < max_gl_contexts &&
         ForciblyEvictedContexts().size()) {
    WebGLRenderingContextBase* evicted_context = OldestEvictedContext();
    if (!evicted_context->restore_allowed_) {
      ForciblyEvictedContexts().erase(evicted_context);
      continue;
    }

    IntSize desired_size = DrawingBuffer::AdjustSize(
        evicted_context->ClampedCanvasSize(), IntSize(),
        evicted_context->max_texture_size_);

    if (!desired_size.IsEmpty()) {
      ForciblyEvictedContexts().erase(evicted_context);
      evicted_context->ForceRestoreContext();
    }
    break;
  }
}
