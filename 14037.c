PluginProcessHost* PluginServiceImpl::FindOrStartNpapiPluginProcess(
    int render_process_id,
    const FilePath& plugin_path) {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::IO));

  if (filter_ && !filter_->CanLoadPlugin(render_process_id, plugin_path))
    return NULL;

  PluginProcessHost* plugin_host = FindNpapiPluginProcess(plugin_path);
  if (plugin_host)
    return plugin_host;

  webkit::WebPluginInfo info;
  if (!GetPluginInfoByPath(plugin_path, &info)) {
    return NULL;
  }

  scoped_ptr<PluginProcessHost> new_host(new PluginProcessHost());
  if (!new_host->Init(info)) {
    NOTREACHED();  // Init is not expected to fail.
    return NULL;
  }
  return new_host.release();
}
