static int do_recv_NPByteRange(rpc_message_t *message, void *p_value)
{
  NPByteRange **rangeListPtr = (NPByteRange **)p_value;
  if (rangeListPtr == NULL)
	return RPC_ERROR_MESSAGE_ARGUMENT_INVALID;
  *rangeListPtr = NULL;

  for (;;) {
	int error;
	uint32_t cont;

	if ((error = rpc_message_recv_uint32(message, &cont)) < 0)
	  return error;
	if (!cont)
	  break;
	NPByteRange *range = malloc(sizeof(*range));
	if (range == NULL)
	  return RPC_ERROR_NO_MEMORY;
	range->next = NULL;
	if ((error = rpc_message_recv_int32(message, &range->offset)) < 0)
	  return error;
	if ((error = rpc_message_recv_uint32(message, &range->length)) < 0)
	  return error;
	*rangeListPtr = range;
	rangeListPtr = &range->next;
  }
  return RPC_ERROR_NO_ERROR;
}
