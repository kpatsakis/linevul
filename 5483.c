 void OffscreenCanvasSurfaceImpl::Create(
    mojo::InterfaceRequest<blink::mojom::OffscreenCanvasSurface> request) {
  mojo::MakeStrongBinding(base::MakeUnique<OffscreenCanvasSurfaceImpl>(),
                          std::move(request));
}
