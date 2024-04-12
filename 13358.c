invoke_NPN_RemoveProperty(PluginInstance *plugin, NPObject *npobj, NPIdentifier propertyName)
{
  npw_return_val_if_fail(rpc_method_invoke_possible(g_rpc_connection), false);

  int error = rpc_method_invoke(g_rpc_connection,
								RPC_METHOD_NPN_REMOVE_PROPERTY,
								RPC_TYPE_NPW_PLUGIN_INSTANCE, plugin,
								RPC_TYPE_NP_OBJECT, npobj,
								RPC_TYPE_NP_IDENTIFIER, &propertyName,
								RPC_TYPE_INVALID);

  if (error != RPC_ERROR_NO_ERROR) {
	npw_perror("NPN_RemoveProperty() invoke", error);
	return false;
  }

  uint32_t ret;
  error = rpc_method_wait_for_reply(g_rpc_connection,
									RPC_TYPE_UINT32, &ret,
									RPC_TYPE_INVALID);

  if (error != RPC_ERROR_NO_ERROR) {
	npw_perror("NPN_RemoveProperty() wait for reply", error);
	return false;
  }

  return ret;
}
