void HTMLInputElement::PostDispatchEventHandler(
    Event* event,
    EventDispatchHandlingState* state) {
  if (!state)
    return;
  input_type_view_->DidDispatchClick(event,
                                     *static_cast<ClickHandlingState*>(state));
}
