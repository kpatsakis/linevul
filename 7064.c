void ForwardRequest(const char* service_name,
                    mojo::InterfaceRequest<Interface> request) {
  service_manager::Connector* connector =
      ServiceManagerConnection::GetForProcess()->GetConnector();
  connector->BindInterface(service_name, std::move(request));
}
