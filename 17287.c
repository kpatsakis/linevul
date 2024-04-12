void ProfilingProcessHost::StartProfilingNonRendererChild(
    int child_process_id,
    base::ProcessId proc_id,
    profiling::mojom::ProcessType process_type) {
  DCHECK(content::BrowserThread::CurrentlyOn(content::BrowserThread::IO));

  content::BrowserChildProcessHost* host =
      content::BrowserChildProcessHost::FromID(child_process_id);
  if (!host)
    return;

  ProfilingClientBinder client(host);
  AddClientToProfilingService(client.take(), proc_id, process_type);
}
