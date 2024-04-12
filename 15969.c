void BrowserChildProcessHostImpl::OnChannelConnected(int32_t peer_pid) {
  DCHECK_CURRENTLY_ON(BrowserThread::IO);

  is_channel_connected_ = true;
  notify_child_disconnected_ = true;

#if defined(OS_WIN)
  early_exit_watcher_.StopWatching();
#endif

  BrowserThread::PostTask(BrowserThread::UI, FROM_HERE,
                          base::BindOnce(&NotifyProcessHostConnected, data_));

  delegate_->OnChannelConnected(peer_pid);

  if (IsProcessLaunched()) {
    ShareMetricsAllocatorToProcess();
    BrowserThread::PostTask(
        BrowserThread::UI, FROM_HERE,
        base::BindOnce(&NotifyProcessLaunchedAndConnected, data_));
  }
}
