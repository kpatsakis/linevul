void RenderProcessHostImpl::CreateRendererHost(
    mojom::RendererHostAssociatedRequest request) {
  renderer_host_binding_.Bind(std::move(request));
}
