int MemBackendImpl::DoomEntriesSince(Time initial_time,
                                     const CompletionCallback& callback) {
  return DoomEntriesBetween(initial_time, Time::Max(), callback);
}
