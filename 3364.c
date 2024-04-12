static int handle_NPP_New(rpc_connection_t *connection)
{
  D(bug("handle_NPP_New\n"));

  rpc_connection_ref(connection);

  uint32_t instance_id;
  NPMIMEType plugin_type;
  int32_t mode;
  int argn_count, argv_count;
  char **argn, **argv;
  NPSavedData *saved;
  int error = rpc_method_get_args(connection,
								  RPC_TYPE_UINT32, &instance_id,
								  RPC_TYPE_STRING, &plugin_type,
								  RPC_TYPE_INT32, &mode,
								  RPC_TYPE_ARRAY, RPC_TYPE_STRING, &argn_count, &argn,
								  RPC_TYPE_ARRAY, RPC_TYPE_STRING, &argv_count, &argv,
								  RPC_TYPE_NP_SAVED_DATA, &saved,
								  RPC_TYPE_INVALID);

  if (error != RPC_ERROR_NO_ERROR) {
	npw_perror("NPP_New() get args", error);
	return error;
  }

  assert(argn_count == argv_count);
  NPError ret = g_NPP_New(plugin_type, instance_id, mode, argn_count, argn, argv, saved);

  if (plugin_type)
	free(plugin_type);
  if (argn) {
	for (int i = 0; i < argn_count; i++)
	  free(argn[i]);
	free(argn);
  }
  if (argv) {
	for (int i = 0; i < argv_count; i++)
	  free(argv[i]);
	free(argv);
  }
  if (saved) {
    if (saved->buf)
      NPN_MemFree(saved->buf);
    NPN_MemFree(saved);
  }

  return rpc_method_send_reply(connection, RPC_TYPE_INT32, ret, RPC_TYPE_INVALID);
}
