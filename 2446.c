ProcessingInstruction* Document::createProcessingInstruction(
    const String& target,
    const String& data,
    ExceptionState& exception_state) {
  if (!IsValidName(target)) {
    exception_state.ThrowDOMException(
        DOMExceptionCode::kInvalidCharacterError,
        "The target provided ('" + target + "') is not a valid name.");
    return nullptr;
  }
  if (data.Contains("?>")) {
    exception_state.ThrowDOMException(
        DOMExceptionCode::kInvalidCharacterError,
        "The data provided ('" + data + "') contains '?>'.");
    return nullptr;
  }
  if (IsHTMLDocument()) {
    UseCounter::Count(*this,
                      WebFeature::kHTMLDocumentCreateProcessingInstruction);
  }
  return ProcessingInstruction::Create(*this, target, data);
}
