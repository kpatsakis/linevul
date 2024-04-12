bool CustomButton::ShouldEnterPushedState(const ui::Event& event) {
  return IsTriggerableEvent(event);
}
