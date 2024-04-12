g_NPN_GetStringIdentifier(const NPUTF8 *name)
{
  if (!thread_check()) {
	npw_printf("WARNING: NPN_GetStringIdentifier not called from the main thread\n");
	return NULL;
  }

  if (name == NULL)
	return NULL;

  D(bugiI("NPN_GetStringIdentifier name='%s'\n", name));
  NPIdentifier ret = cached_NPN_GetStringIdentifier(name);
  D(bugiD("NPN_GetStringIdentifier return: %p\n", ret));
  return ret;
}
