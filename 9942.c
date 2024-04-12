RenderProcessHostImpl::GetSpareRenderProcessHostForTesting() {
  return g_spare_render_process_host_manager.Get().spare_render_process_host();
}
