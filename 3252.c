  static void Register(BrowserContext* browser_context,
                       RenderProcessHost* render_process_host,
                       const GURL& site_url) {
    DCHECK(!site_url.is_empty());
    if (!ShouldTrackProcessForSite(browser_context, render_process_host,
                                   site_url))
      return;

    UnmatchedServiceWorkerProcessTracker* tracker =
        static_cast<UnmatchedServiceWorkerProcessTracker*>(
            browser_context->GetUserData(
                kUnmatchedServiceWorkerProcessTrackerKey));
    if (!tracker) {
      tracker = new UnmatchedServiceWorkerProcessTracker();
      browser_context->SetUserData(kUnmatchedServiceWorkerProcessTrackerKey,
                                   base::WrapUnique(tracker));
    }
    tracker->RegisterProcessForSite(render_process_host, site_url);
  }
