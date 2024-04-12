History* LocalDOMWindow::history() const {
  if (!history_)
    history_ = History::Create(GetFrame());
  return history_.Get();
}
