void PluginServiceImpl::CancelOpenChannelToNpapiPlugin(
    PluginProcessHost::Client* client) {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::IO));
  DCHECK(ContainsKey(pending_plugin_clients_, client));
  pending_plugin_clients_.erase(client);
}
