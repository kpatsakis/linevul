  void Create(service_manager::mojom::ServiceFactoryRequest request) {
    service_factory_bindings_.AddBinding(this, std::move(request));
  }
