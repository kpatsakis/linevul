void BrowserRenderProcessHost::OnProcessLaunched() {
  if (deleting_soon_)
    return;

  if (child_process_launcher_.get())
    child_process_launcher_->SetProcessBackgrounded(backgrounded_);

  if (max_page_id_ != -1)
    Send(new ViewMsg_SetNextPageID(max_page_id_ + 1));

  NotificationService::current()->Notify(
      content::NOTIFICATION_RENDERER_PROCESS_CREATED,
      Source<RenderProcessHost>(this), NotificationService::NoDetails());

  while (!queued_messages_.empty()) {
    Send(queued_messages_.front());
    queued_messages_.pop();
  }
}
