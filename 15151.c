void ChromeRenderMessageFilter::OnFPS(int routing_id, float fps) {
  if (!BrowserThread::CurrentlyOn(BrowserThread::UI)) {
    BrowserThread::PostTask(
        BrowserThread::UI, FROM_HERE,
        base::Bind(
            &ChromeRenderMessageFilter::OnFPS, this,
            routing_id, fps));
    return;
  }

  base::ProcessId renderer_id = base::GetProcId(peer_handle());

#if defined(ENABLE_TASK_MANAGER)
  TaskManager::GetInstance()->model()->NotifyFPS(
      renderer_id, routing_id, fps);
#endif  // defined(ENABLE_TASK_MANAGER)

  FPSDetails details(routing_id, fps);
  content::NotificationService::current()->Notify(
      chrome::NOTIFICATION_RENDERER_FPS_COMPUTED,
      content::Source<const base::ProcessId>(&renderer_id),
      content::Details<const FPSDetails>(&details));
}
