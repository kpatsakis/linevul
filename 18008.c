WebGLRenderingContextBaseMap& ForciblyEvictedContexts() {
  DEFINE_THREAD_SAFE_STATIC_LOCAL(ThreadSpecific<WebGLRenderingContextBaseMap>,
                                  forcibly_evicted_contexts, ());
  if (!forcibly_evicted_contexts.IsSet())
    forcibly_evicted_contexts->RegisterAsStaticReference();
  return *forcibly_evicted_contexts;
}
