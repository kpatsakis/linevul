base::OnceClosure DesktopWindowTreeHostX11::DisableEventListening() {
  modal_dialog_counter_++;
  if (modal_dialog_counter_ == 1) {
    targeter_for_modal_ = std::make_unique<aura::ScopedWindowTargeter>(
        window(), std::make_unique<aura::NullWindowTargeter>());
  }

  return base::BindOnce(&DesktopWindowTreeHostX11::EnableEventListening,
                        weak_factory_.GetWeakPtr());
}
