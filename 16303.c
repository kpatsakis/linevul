void TestWebKitPlatformSupport::GetPlugins(
    bool refresh, std::vector<webkit::WebPluginInfo>* plugins) {
  if (refresh)
    webkit::npapi::PluginList::Singleton()->RefreshPlugins();
  webkit::npapi::PluginList::Singleton()->GetPlugins(plugins);
  const FilePath::StringType kPluginBlackList[] = {
    FILE_PATH_LITERAL("npapi_layout_test_plugin.dll"),
    FILE_PATH_LITERAL("WebKitTestNetscapePlugIn.plugin"),
    FILE_PATH_LITERAL("libnpapi_layout_test_plugin.so"),
  };
  for (int i = plugins->size() - 1; i >= 0; --i) {
    webkit::WebPluginInfo plugin_info = plugins->at(i);
    for (size_t j = 0; j < arraysize(kPluginBlackList); ++j) {
      if (plugin_info.path.BaseName() == FilePath(kPluginBlackList[j])) {
        plugins->erase(plugins->begin() + i);
      }
    }
  }
}
