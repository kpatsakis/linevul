void PluginDataRemover::GetSupportedPlugins(
    std::vector<WebPluginInfo>* supported_plugins) {
  bool allow_wildcard = false;
  std::vector<WebPluginInfo> plugins;
  PluginService::GetInstance()->GetPluginInfoArray(
      GURL(), kFlashPluginSwfMimeType, allow_wildcard, &plugins, NULL);
  Version min_version(kMinFlashVersion);
  for (std::vector<WebPluginInfo>::iterator it = plugins.begin();
       it != plugins.end(); ++it) {
    Version version;
    WebPluginInfo::CreateVersionFromString(it->version, &version);
    if (version.IsValid() && min_version.CompareTo(version) == -1)
      supported_plugins->push_back(*it);
  }
}
