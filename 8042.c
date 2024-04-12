void PluginServiceImpl::GetAllowedPluginForOpenChannelToPlugin(
    int render_process_id,
    int render_view_id,
    const GURL& url,
    const GURL& page_url,
    const std::string& mime_type,
    PluginProcessHost::Client* client,
    ResourceContext* resource_context) {
  webkit::WebPluginInfo info;
  bool allow_wildcard = true;
  bool found = GetPluginInfo(
      render_process_id, render_view_id, resource_context,
      url, page_url, mime_type, allow_wildcard,
      NULL, &info, NULL);
  FilePath plugin_path;
  if (found)
    plugin_path = info.path;

  BrowserThread::PostTask(
      BrowserThread::IO, FROM_HERE,
      base::Bind(&PluginServiceImpl::FinishOpenChannelToPlugin,
                 base::Unretained(this),
                 render_process_id,
                 plugin_path,
                 client));
}
