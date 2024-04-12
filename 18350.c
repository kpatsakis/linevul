bool ContextMenuFilter::OnMessageReceived(const IPC::Message& message) {
  DCHECK_CURRENTLY_ON(content::BrowserThread::IO);
  if (message.type() == FrameHostMsg_ContextMenu::ID) {
    FrameHostMsg_ContextMenu::Param params;
    FrameHostMsg_ContextMenu::Read(&message, &params);
    content::ContextMenuParams menu_params = std::get<0>(params);
    content::BrowserThread::PostTask(
        content::BrowserThread::UI, FROM_HERE,
        base::BindOnce(&ContextMenuFilter::OnContextMenu, this, menu_params));
  }
  return false;
}
