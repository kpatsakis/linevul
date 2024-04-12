void P2PSocketDispatcherHost::OnGetNetworkList(const IPC::Message& msg) {
  BrowserThread::PostTask(
      BrowserThread::FILE, FROM_HERE, NewRunnableMethod(
          this, &P2PSocketDispatcherHost::DoGetNetworkList, msg.routing_id()));
}
