bool PluginModule::InitAsInternalPlugin(const EntryPoints& entry_points) {
  if (InitializeModule(entry_points)) {
    entry_points_ = entry_points;
    return true;
  }
  return false;
}
