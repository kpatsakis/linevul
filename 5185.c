void RenderFrameImpl::BindServiceRegistry(
    mojo::InterfaceRequest<mojo::ServiceProvider> services,
    mojo::ServiceProviderPtr exposed_services) {
  service_registry_.Bind(services.Pass());
  service_registry_.BindRemoteServiceProvider(exposed_services.Pass());
}
