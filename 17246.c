static int do_test(void)
{
  if (g_plugin_NP_GetMIMEDescription == NULL)
	return 1;
  if (g_plugin_NP_Initialize == NULL)
	return 2;
  if (g_plugin_NP_Shutdown == NULL)
	return 3;
  if (is_flash_player9_beta1())
	return 4;
  return 0;
}
