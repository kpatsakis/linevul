DOMWindow* Document::open(v8::Isolate* isolate,
                          const USVStringOrTrustedURL& string_or_url,
                          const AtomicString& name,
                          const AtomicString& features,
                          ExceptionState& exception_state) {
  if (!domWindow()) {
    exception_state.ThrowDOMException(DOMExceptionCode::kInvalidAccessError,
                                      "The document has no window associated.");
    return nullptr;
  }

  return domWindow()->open(isolate, string_or_url, name, features,
                           exception_state);
}
