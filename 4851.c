bool BrowserView::CanActivate() const {
  if (!AppModalDialogQueue::GetInstance()->active_dialog())
    return true;

  MessageLoop::current()->PostTask(
      FROM_HERE,
      base::Bind(&BrowserView::ActivateAppModalDialog,
                 activate_modal_dialog_factory_.GetWeakPtr()));
  return false;
}
