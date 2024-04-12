void OmniboxViewViews::Update() {
  if (model()->ResetDisplayTexts()) {
    RevertAll();

    if (model()->has_focus()) {
      SelectAllForUserGesture();
    }
  } else {
    EmphasizeURLComponents();
  }
}
