static int do_recv_NotifyData(rpc_message_t *message, void *p_value)
{
  int error;
  uint64_t id;

  if ((error = rpc_message_recv_uint64(message, &id)) < 0)
	return error;

  if (sizeof(void *) == 4 && ((uint32_t)(id >> 32)) != 0) {
	npw_printf("ERROR: 64-bit viewers in 32-bit wrappers are not supported\n");
	abort();
  }

  *((void **)p_value) = (void *)(uintptr_t)id;
  return RPC_ERROR_NO_ERROR;
}
