static int handle_NP_GetValue(rpc_connection_t *connection)
{
  D(bug("handle_NP_GetValue\n"));

  int32_t variable;
  int error = rpc_method_get_args(connection, RPC_TYPE_INT32, &variable, RPC_TYPE_INVALID);
  if (error != RPC_ERROR_NO_ERROR) {
	npw_perror("NP_GetValue() get args", error);
	return error;
  }

  NPError ret = NPERR_GENERIC_ERROR;
  int variable_type = rpc_type_of_NPPVariable(variable);

  switch (variable_type) {
  case RPC_TYPE_STRING:
	{
	  char *str = NULL;
	  ret = g_NP_GetValue(variable, (void *)&str);
	  return rpc_method_send_reply(connection, RPC_TYPE_INT32, ret, RPC_TYPE_STRING, str, RPC_TYPE_INVALID);
	}
  case RPC_TYPE_INT32:
	{
	  uint32_t n = 0;
	  ret = g_NP_GetValue(variable, (void *)&n);
	  return rpc_method_send_reply(connection, RPC_TYPE_INT32, ret, RPC_TYPE_INT32, n, RPC_TYPE_INVALID);
	}
  case RPC_TYPE_BOOLEAN:
	{
	  NPBool b = FALSE;
	  ret = g_NP_GetValue(variable, (void *)&b);
	  return rpc_method_send_reply(connection, RPC_TYPE_INT32, ret, RPC_TYPE_BOOLEAN, b, RPC_TYPE_INVALID);
	}
  }

  npw_printf("ERROR: only basic types are supported in NP_GetValue()\n");
  abort();
}
