void DesktopWindowTreeHostX11::EnableEventListening() {
  DCHECK_GT(modal_dialog_counter_, 0UL);
  if (!--modal_dialog_counter_)
    targeter_for_modal_.reset();
}
