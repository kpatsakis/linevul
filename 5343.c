void RenderProcessHostImpl::set_render_process_host_factory(
    const RenderProcessHostFactory* rph_factory) {
  g_render_process_host_factory_ = rph_factory;
}
