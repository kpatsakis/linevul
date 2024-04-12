  void FindRenderProcessesForSite(
      const GURL& site_url,
      std::set<RenderProcessHost*>* foreground_processes,
      std::set<RenderProcessHost*>* background_processes) {
    auto result = map_.find(site_url);
    if (result == map_.end())
      return;

    std::map<ProcessID, Count>& counts_per_process = result->second;
    for (auto iter : counts_per_process) {
      RenderProcessHost* host = RenderProcessHost::FromID(iter.first);
      if (!host) {
        NOTREACHED();
        continue;
      }

      if (!host->MayReuseHost() ||
          !RenderProcessHostImpl::IsSuitableHost(
              host, host->GetBrowserContext(), site_url))
        continue;

      if (host->VisibleWidgetCount())
        foreground_processes->insert(host);
      else
        background_processes->insert(host);
    }
  }
