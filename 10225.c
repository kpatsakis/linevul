MojoResult Core::DuplicateBufferHandle(
    MojoHandle buffer_handle,
    const MojoDuplicateBufferHandleOptions* options,
    MojoHandle* new_buffer_handle) {
  RequestContext request_context;
  scoped_refptr<Dispatcher> dispatcher(GetDispatcher(buffer_handle));
  if (!dispatcher)
    return MOJO_RESULT_INVALID_ARGUMENT;

  scoped_refptr<Dispatcher> new_dispatcher;
  MojoResult result =
      dispatcher->DuplicateBufferHandle(options, &new_dispatcher);
  if (result != MOJO_RESULT_OK)
    return result;

  *new_buffer_handle = AddDispatcher(new_dispatcher);
  if (*new_buffer_handle == MOJO_HANDLE_INVALID) {
    LOG(ERROR) << "Handle table full";
    new_dispatcher->Close();
    return MOJO_RESULT_RESOURCE_EXHAUSTED;
  }

  return MOJO_RESULT_OK;
}
