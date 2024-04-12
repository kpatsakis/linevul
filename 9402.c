bool SharedWorkerDevToolsAgentHost::Close() {
  if (worker_host_)
    worker_host_->TerminateWorker();
   return true;
 }
