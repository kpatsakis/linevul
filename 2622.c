bool Textfield::AcceleratorPressed(const ui::Accelerator& accelerator) {
  ui::KeyEvent event(
      accelerator.key_state() == ui::Accelerator::KeyState::PRESSED
          ? ui::ET_KEY_PRESSED
          : ui::ET_KEY_RELEASED,
      accelerator.key_code(), accelerator.modifiers());
  ExecuteTextEditCommand(GetCommandForKeyEvent(event));
  return true;
}
