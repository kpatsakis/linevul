void NotifyPluginsOfActivation() {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::IO));

  for (PluginProcessHostIterator iter; !iter.Done(); ++iter)
    iter->OnAppActivation();
}
