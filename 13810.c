::TabCloseableStateWatcher* ::TabCloseableStateWatcher::Create() {
  ::TabCloseableStateWatcher* watcher = NULL;
#if defined(OS_CHROMEOS)
  if (!CommandLine::ForCurrentProcess()->HasSwitch(
      switches::kDisableTabCloseableStateWatcher))
    watcher = new chromeos::TabCloseableStateWatcher();
#endif  // OS_CHROMEOS
  if (!watcher)
    watcher = new ::TabCloseableStateWatcher();
  return watcher;
}
