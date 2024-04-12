std::unique_ptr<ServiceManagerConnection> ServiceManagerConnection::Create(
    service_manager::mojom::ServiceRequest request,
    scoped_refptr<base::SequencedTaskRunner> io_task_runner) {
  if (service_manager_connection_factory)
    return service_manager_connection_factory->Run();
  return base::MakeUnique<ServiceManagerConnectionImpl>(
      std::move(request), io_task_runner);
}
