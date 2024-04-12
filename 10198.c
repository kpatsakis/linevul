void BrowserChildProcessHostImpl::TerminateAll() {
  DCHECK_CURRENTLY_ON(BrowserThread::IO);
  BrowserChildProcessList copy = g_child_process_list.Get();
  for (BrowserChildProcessList::iterator it = copy.begin();
       it != copy.end(); ++it) {
    delete (*it)->delegate();  // ~*HostDelegate deletes *HostImpl.
  }
}
