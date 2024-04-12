bool LoadEntryPointsFromLibrary(const base::NativeLibrary& library,
                                PluginModule::EntryPoints* entry_points) {
  entry_points->get_interface =
      reinterpret_cast<PluginModule::GetInterfaceFunc>(
          base::GetFunctionPointerFromNativeLibrary(library,
                                                    "PPP_GetInterface"));
  if (!entry_points->get_interface) {
    LOG(WARNING) << "No PPP_GetInterface in plugin library";
    return false;
  }

  entry_points->initialize_module =
      reinterpret_cast<PluginModule::PPP_InitializeModuleFunc>(
          base::GetFunctionPointerFromNativeLibrary(library,
                                                    "PPP_InitializeModule"));
  if (!entry_points->initialize_module) {
    LOG(WARNING) << "No PPP_InitializeModule in plugin library";
    return false;
  }

  entry_points->shutdown_module =
      reinterpret_cast<PluginModule::PPP_ShutdownModuleFunc>(
          base::GetFunctionPointerFromNativeLibrary(library,
                                                    "PPP_ShutdownModule"));

  return true;
}
