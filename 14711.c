TabCloseableStateWatcher::~TabCloseableStateWatcher() {
  BrowserList::RemoveObserver(this);
  if (!browser_shutdown::ShuttingDownWithoutClosingBrowsers())
    DCHECK(tabstrip_watchers_.empty());
}
