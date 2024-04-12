NPError PluginInstance::NPP_DestroyStream(NPStream *stream, NPReason reason) {
  DCHECK(npp_functions_ != 0);
  DCHECK(npp_functions_->destroystream != 0);

  if (stream == NULL || !IsValidStream(stream) || (stream->ndata == NULL))
    return NPERR_INVALID_INSTANCE_ERROR;

  if (npp_functions_->destroystream != 0) {
    NPError result = npp_functions_->destroystream(npp_, stream, reason);
    stream->ndata = NULL;
    return result;
  }
  return NPERR_INVALID_FUNCTABLE_ERROR;
}
