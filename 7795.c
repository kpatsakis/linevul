void HTMLFormElement::Trace(blink::Visitor* visitor) {
  visitor->Trace(past_names_map_);
  visitor->Trace(radio_button_group_scope_);
  visitor->Trace(listed_elements_);
  visitor->Trace(image_elements_);
  visitor->Trace(planned_navigation_);
  HTMLElement::Trace(visitor);
}
