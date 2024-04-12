void PluginServiceImpl::ForwardGetAllowedPluginForOpenChannelToPlugin(
    const PluginServiceFilterParams& params,
    const GURL& url,
    const std::string& mime_type,
    PluginProcessHost::Client* client,
    const std::vector<webkit::WebPluginInfo>&) {
  GetAllowedPluginForOpenChannelToPlugin(params.render_process_id,
      params.render_view_id, url, params.page_url, mime_type, client,
      params.resource_context);
}
