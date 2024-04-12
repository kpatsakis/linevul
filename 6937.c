g_NPN_RetainObject(NPObject *npobj)
{
  if (!thread_check()) {
	npw_printf("WARNING: NPN_RetainObject not called from the main thread\n");
	return NULL;
  }
	
  if (npobj == NULL)
	return NULL;

  D(bugiI("NPN_RetainObject npobj=%p\n", npobj));
  uint32_t refcount = invoke_NPN_RetainObject(npobj);
  D(bugiD("NPN_RetainObject return: %p (refcount: %d)\n", npobj, refcount));
  npobj->referenceCount = refcount;
  return npobj;
}
