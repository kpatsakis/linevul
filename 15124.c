WebString WebLocalFrameImpl::Prompt(const WebString& message,
                                    const WebString& default_value) {
  DCHECK(GetFrame());
  ScriptState* script_state = ToScriptStateForMainWorld(GetFrame());
  DCHECK(script_state);
  return GetFrame()->DomWindow()->prompt(script_state, message, default_value);
}
