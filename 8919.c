g_NP_GetValue(NPPVariable variable, void *value)
{
  if (g_plugin_NP_GetValue == NULL)
	return NPERR_INVALID_FUNCTABLE_ERROR;

  D(bugiI("NP_GetValue variable=%d [%s]\n", variable, string_of_NPPVariable(variable)));
  NPError ret = g_plugin_NP_GetValue(NULL, variable, value);
  D(bugiD("NP_GetValue return: %d\n", ret));
  return ret;
}
