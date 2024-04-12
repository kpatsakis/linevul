void Textfield::OnEnabledChanged() {
  View::OnEnabledChanged();
  if (GetInputMethod())
    GetInputMethod()->OnTextInputTypeChanged(this);
  SchedulePaint();
}
