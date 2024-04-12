static int handle_NPP_SetWindow(rpc_connection_t *connection)
{
  D(bug("handle_NPP_SetWindow\n"));

  int error;
  PluginInstance *plugin;
  NPWindow *window;

  error = rpc_method_get_args(connection,
							  RPC_TYPE_NPW_PLUGIN_INSTANCE, &plugin,
							  RPC_TYPE_NP_WINDOW, &window,
							  RPC_TYPE_INVALID);

  if (error != RPC_ERROR_NO_ERROR) {
	npw_perror("NPP_SetWindow() get args", error);
	return error;
  }

  NPError ret = g_NPP_SetWindow(PLUGIN_INSTANCE_NPP(plugin), window);

  if (window) {
	if (window->ws_info) {
	  free(window->ws_info);
	  window->ws_info = NULL;
	}
	free(window);
  }

  return rpc_method_send_reply(connection, RPC_TYPE_INT32, ret, RPC_TYPE_INVALID);
}
