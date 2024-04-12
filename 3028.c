ScriptProcessorNode* BaseAudioContext::createScriptProcessor(
    ExceptionState& exception_state) {
  DCHECK(IsMainThread());

  return ScriptProcessorNode::Create(*this, exception_state);
}
