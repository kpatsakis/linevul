static void CountEditingEvent(ExecutionContext* execution_context,
                              const Event* event,
                              WebFeature feature_on_input,
                              WebFeature feature_on_text_area,
                              WebFeature feature_on_content_editable,
                              WebFeature feature_on_non_node) {
  EventTarget* event_target = event->target();
  Node* node = event_target->ToNode();
  if (!node) {
    UseCounter::Count(execution_context, feature_on_non_node);
    return;
  }

  if (isHTMLInputElement(node)) {
    UseCounter::Count(execution_context, feature_on_input);
    return;
  }

  if (isHTMLTextAreaElement(node)) {
    UseCounter::Count(execution_context, feature_on_text_area);
    return;
  }

  TextControlElement* control = EnclosingTextControl(node);
  if (isHTMLInputElement(control)) {
    UseCounter::Count(execution_context, feature_on_input);
    return;
  }

  if (isHTMLTextAreaElement(control)) {
    UseCounter::Count(execution_context, feature_on_text_area);
    return;
  }

  UseCounter::Count(execution_context, feature_on_content_editable);
}
