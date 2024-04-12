g_NPN_IdentifierIsString(NPIdentifier identifier)
{
  if (!thread_check()) {
	npw_printf("WARNING: NPN_IdentifierIsString not called from the main thread\n");
	return false;
  }
  
  D(bugiI("NPN_IdentifierIsString identifier=%p\n", identifier));
  bool ret = invoke_NPN_IdentifierIsString(identifier);
  D(bugiD("NPN_IdentifierIsString return: %d\n", ret));
  return ret;
}
