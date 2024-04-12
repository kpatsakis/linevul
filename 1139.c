void RenderProcessHostImpl::RegisterRendererMainThreadFactory(
    RendererMainThreadFactoryFunction create) {
  g_renderer_main_thread_factory = create;
}
