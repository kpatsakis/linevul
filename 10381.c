void RenderFrameDevToolsAgentHost::ApplyOverrides(
    FrameTreeNode* frame_tree_node,
    mojom::BeginNavigationParams* begin_params,
    bool* report_raw_headers) {
  bool disable_cache = false;
  frame_tree_node = GetFrameTreeNodeAncestor(frame_tree_node);
  RenderFrameDevToolsAgentHost* agent_host = FindAgentHost(frame_tree_node);
  if (!agent_host)
    return;
  net::HttpRequestHeaders headers;
  headers.AddHeadersFromString(begin_params->headers);
  for (auto* network : protocol::NetworkHandler::ForAgentHost(agent_host)) {
    if (!network->enabled())
      continue;
    *report_raw_headers = true;
    network->ApplyOverrides(&headers, &begin_params->skip_service_worker,
                            &disable_cache);
  }
  if (disable_cache) {
    begin_params->load_flags &=
        ~(net::LOAD_VALIDATE_CACHE | net::LOAD_SKIP_CACHE_VALIDATION |
          net::LOAD_ONLY_FROM_CACHE | net::LOAD_DISABLE_CACHE);
    begin_params->load_flags |= net::LOAD_BYPASS_CACHE;
  }

  begin_params->headers = headers.ToString();
}
