OmniboxState::OmniboxState(const OmniboxEditModel::State& model_state,
                           const gfx::Range& selection,
                           const gfx::Range& saved_selection_for_focus_change)
    : model_state(model_state),
      selection(selection),
      saved_selection_for_focus_change(saved_selection_for_focus_change) {
}
