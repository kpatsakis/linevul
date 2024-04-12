DOMWindow* Document::open(LocalDOMWindow* current_window,
                          LocalDOMWindow* entered_window,
                          const USVStringOrTrustedURL& stringOrUrl,
                          const AtomicString& name,
                          const AtomicString& features,
                          ExceptionState& exception_state) {
  if (!domWindow()) {
    exception_state.ThrowDOMException(DOMExceptionCode::kInvalidAccessError,
                                      "The document has no window associated.");
    return nullptr;
  }
  AtomicString frame_name = name.IsEmpty() ? "_blank" : name;

  return domWindow()->open(stringOrUrl, frame_name, features, current_window,
                           entered_window, exception_state);
}
