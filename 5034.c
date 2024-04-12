PpapiPluginProcessHost* PluginServiceImpl::FindPpapiBrokerProcess(
    const FilePath& broker_path) {
  for (PpapiBrokerProcessHostIterator iter; !iter.Done(); ++iter) {
    if (iter->plugin_path() == broker_path)
      return *iter;
  }

  return NULL;
}
