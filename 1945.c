void WindowTreeHostManager::CreatePrimaryHost(
    const AshWindowTreeHostInitParams& init_params) {
  const display::Display& primary_candidate =
      GetDisplayManager()->GetPrimaryDisplayCandidate();
  primary_display_id = primary_candidate.id();
  CHECK_NE(display::Display::kInvalidDisplayID, primary_display_id);
  AddWindowTreeHostForDisplay(primary_candidate, init_params);
}
