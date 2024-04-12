MojoResult DataPipeProducerDispatcher::AddWatcherRef(
    const scoped_refptr<WatcherDispatcher>& watcher,
    uintptr_t context) {
  base::AutoLock lock(lock_);
  if (is_closed_ || in_transit_)
    return MOJO_RESULT_INVALID_ARGUMENT;
  return watchers_.Add(watcher, context, GetHandleSignalsStateNoLock());
}
