void Textfield::ExecuteCommand(int command_id, int event_flags) {
  if (text_services_context_menu_ &&
      text_services_context_menu_->SupportsCommand(command_id)) {
    text_services_context_menu_->ExecuteCommand(command_id);
    return;
  }

  Textfield::ExecuteTextEditCommand(
      GetTextEditCommandFromMenuCommand(command_id, HasSelection()));
}
