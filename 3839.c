  void OnShowWidget(int routing_id, const gfx::Rect& initial_rect) {
    content::BrowserThread::PostTask(
        content::BrowserThread::UI, FROM_HERE,
        base::BindOnce(&PendingWidgetMessageFilter::OnReceivedRoutingIDOnUI,
                       this, routing_id));
  }
