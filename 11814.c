void IOThread::ClearHostCache() {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::IO));

  net::HostCache* host_cache = globals_->host_resolver->GetHostCache();
  if (host_cache)
    host_cache->clear();
}
