void ServiceManagerConnection::SetFactoryForTest(Factory* factory) {
  DCHECK(!g_connection_for_process.Get());
  service_manager_connection_factory = factory;
}
