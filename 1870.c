ThreadWatcherList::ThreadWatcherList() {
  DCHECK(WatchDogThread::CurrentlyOnWatchDogThread());
  CHECK(!g_thread_watcher_list_);
  g_thread_watcher_list_ = this;
}
