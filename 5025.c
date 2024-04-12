service_manager::Connector* DownloadManagerImpl::GetServiceManagerConnector() {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  if (auto* connection = ServiceManagerConnection::GetForProcess())
    return connection->GetConnector();
  return nullptr;
}
