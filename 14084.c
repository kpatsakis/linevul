void DevToolsUIBindings::StopIndexing(int index_request_id) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  IndexingJobsMap::iterator it = indexing_jobs_.find(index_request_id);
  if (it == indexing_jobs_.end())
    return;
  it->second->Stop();
  indexing_jobs_.erase(it);
}
