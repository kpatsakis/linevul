void NotifyOnUI(int type, int render_process_id, int render_view_id,
                scoped_ptr<T> detail) {
  RenderViewHostImpl* host =
      RenderViewHostImpl::FromID(render_process_id, render_view_id);
  if (host) {
    RenderViewHostDelegate* delegate = host->GetDelegate();
    NotificationService::current()->Notify(
        type, Source<WebContents>(delegate->GetAsWebContents()),
        Details<T>(detail.get()));
  }
}
