void NPN_PluginThreadAsyncCall(NPP id,
                               void (*func)(void*),
                               void* user_data) {
  scoped_refptr<NPAPI::PluginInstance> plugin = FindInstance(id);
  if (plugin)
    plugin->PluginThreadAsyncCall(func, user_data);
}
