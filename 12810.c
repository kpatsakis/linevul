GpuProcessHost* GpuProcessHost::FromID(int host_id) {
  DCHECK_CURRENTLY_ON(BrowserThread::IO);

  for (int i = 0; i < GPU_PROCESS_KIND_COUNT; ++i) {
    GpuProcessHost* host = g_gpu_process_hosts[i];
    if (host && host->host_id_ == host_id && ValidateHost(host))
      return host;
  }

  return nullptr;
}
