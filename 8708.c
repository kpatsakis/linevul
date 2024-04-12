g_NPP_WriteReady(NPP instance, NPStream *stream)
{
  if (instance == NULL)
	return 0;

  if (plugin_funcs.writeready == NULL)
	return 0;

  if (stream == NULL)
	return 0;

  D(bugiI("NPP_WriteReady instance=%p, stream=%p\n", instance, stream));
  int32_t ret = plugin_funcs.writeready(instance, stream);
  D(bugiD("NPP_WriteReady return: %d\n", ret));
  return ret;
}
