void HTMLMediaElement::RejectPlayPromisesInternal(ExceptionCode code,
                                                  const String& message) {
  DCHECK(code == kAbortError || code == kNotSupportedError);

  for (auto& resolver : play_promise_reject_list_)
    resolver->Reject(DOMException::Create(code, message));

  play_promise_reject_list_.clear();
}
