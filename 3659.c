ServiceManagerContext::~ServiceManagerContext() {
  if (in_process_context_)
    in_process_context_->ShutDown();
  if (ServiceManagerConnection::GetForProcess())
    ServiceManagerConnection::DestroyForProcess();
  BrowserThread::PostTask(BrowserThread::IO, FROM_HERE,
                          base::Bind(&DestroyConnectorOnIOThread));
}
