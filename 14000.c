void PreconnectManager::StartPreconnectUrl(
    const GURL& url,
    bool allow_credentials,
    net::NetworkIsolationKey network_isolation_key) {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
  if (!url.SchemeIsHTTPOrHTTPS())
    return;
  PreresolveJobId job_id = preresolve_jobs_.Add(std::make_unique<PreresolveJob>(
      url.GetOrigin(), 1, allow_credentials, std::move(network_isolation_key),
      nullptr));
  queued_jobs_.push_front(job_id);

  TryToLaunchPreresolveJobs();
}
