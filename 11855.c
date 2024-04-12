TabletModeWindowState::TabletModeWindowState(aura::Window* window,
                                             TabletModeWindowManager* creator,
                                             bool snap,
                                             bool animate_bounds_on_attach,
                                             bool entering_tablet_mode)
    : window_(window),
      creator_(creator),
      animate_bounds_on_attach_(animate_bounds_on_attach) {
  wm::WindowState* state = wm::GetWindowState(window);
  current_state_type_ = state->GetStateType();
  DCHECK(!snap || CanSnapInSplitview(window));
  state_type_on_attach_ =
      snap ? current_state_type_ : GetMaximizedOrCenteredWindowType(state);
  if (entering_tablet_mode)
    set_enter_animation_type(IsTopWindow(window) ? DEFAULT : STEP_END);
  old_state_.reset(
      state->SetStateObject(std::unique_ptr<State>(this)).release());
}
