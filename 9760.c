bool OmniboxViewViews::IsImeShowingPopup() const {
#if defined(OS_CHROMEOS)
  return ime_candidate_window_open_;
#else
  const views::InputMethod* input_method = this->GetInputMethod();
  return input_method && input_method->IsCandidatePopupOpen();
#endif
}
