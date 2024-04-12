NPError WebPluginDelegatePepper::Device2DFlushContext(
    NPP id,
    NPDeviceContext2D* context,
    NPDeviceFlushContextCallbackPtr callback,
    void* user_data) {
  if (!context)
    return NPERR_INVALID_PARAM;

  Graphics2DDeviceContext* ctx = graphic2d_contexts_.Lookup(
      reinterpret_cast<intptr_t>(context->reserved));
  if (!ctx)
    return NPERR_INVALID_PARAM;  // TODO(brettw) call callback.

  return ctx->Flush(&committed_bitmap_, context, callback, id, user_data);
}
