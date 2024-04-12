void RenderProcessHost::PostTaskWhenProcessIsReady(base::OnceClosure task) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  DCHECK(!task.is_null());
  new RenderProcessHostIsReadyObserver(this, std::move(task));
}
