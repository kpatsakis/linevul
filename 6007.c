static int do_send_NPIdentifier(rpc_message_t *message, void *p_value)
{
  NPIdentifier ident = *(NPIdentifier *)p_value;
  int id = 0;
  if (ident) {
#ifdef BUILD_WRAPPER
	id = id_lookup_value(ident);
	if (id < 0)
	  id = id_create(ident);
#endif
#ifdef BUILD_VIEWER
	id = (uintptr_t)ident;
#endif
	assert(id != 0);
  }
  return rpc_message_send_uint32(message, id);
}
