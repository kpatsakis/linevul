SessionCommand* SessionService::CreatePinnedStateCommand(
    const SessionID& tab_id,
    bool is_pinned) {
  PinnedStatePayload payload = { 0 };
  payload.tab_id = tab_id.id();
  payload.pinned_state = is_pinned;
  SessionCommand* command =
      new SessionCommand(kCommandSetPinnedState, sizeof(payload));
  memcpy(command->contents(), &payload, sizeof(payload));
  return command;
}
