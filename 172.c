void DispatchInputEvent(Element* target,
                        InputEvent::InputType input_type,
                        const String& data,
                        InputEvent::EventIsComposing is_composing) {
  if (!RuntimeEnabledFeatures::InputEventEnabled())
    return;
  if (!target)
    return;
  InputEvent* input_event =
      InputEvent::CreateInput(input_type, data, is_composing, nullptr);
  target->DispatchScopedEvent(input_event);
}
