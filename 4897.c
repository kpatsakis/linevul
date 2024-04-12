void WebGLRenderingContextBase::ActivateContext(
    WebGLRenderingContextBase* context) {
  unsigned max_gl_contexts = CurrentMaxGLContexts();
  unsigned removed_contexts = 0;
  while (ActiveContexts().size() >= max_gl_contexts &&
         removed_contexts < max_gl_contexts) {
    ForciblyLoseOldestContext(
        "WARNING: Too many active WebGL contexts. Oldest context will be "
        "lost.");
    removed_contexts++;
  }

  DCHECK(!context->isContextLost());
  ActiveContexts().insert(context);
}
