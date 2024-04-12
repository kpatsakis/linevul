DevToolsAgentHost::List GetBrowserAgentHosts() {
  DevToolsAgentHost::List result;
  for (const auto& id_host : g_devtools_instances.Get()) {
    if (id_host.second->GetType() == DevToolsAgentHost::kTypeBrowser)
      result.push_back(id_host.second);
  }
  return result;
}
