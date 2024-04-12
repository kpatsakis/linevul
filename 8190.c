void PPB_URLLoader_Impl::RunCallback(int32_t result) {
  if (!pending_callback_.get()) {
    return;
  }

  scoped_refptr<TrackedCompletionCallback> callback;
  callback.swap(pending_callback_);
  callback->Run(result);  // Will complete abortively if necessary.
}
