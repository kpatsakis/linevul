MediaElementAudioSourceNode* MediaElementAudioSourceNode::Create(
    AudioContext& context,
    HTMLMediaElement& media_element,
    ExceptionState& exception_state) {
  DCHECK(IsMainThread());

  if (context.IsContextClosed()) {
    context.ThrowExceptionForClosedState(exception_state);
    return nullptr;
  }

  if (media_element.AudioSourceNode()) {
    exception_state.ThrowDOMException(DOMExceptionCode::kInvalidStateError,
                                      "HTMLMediaElement already connected "
                                      "previously to a different "
                                      "MediaElementSourceNode.");
    return nullptr;
  }

  MediaElementAudioSourceNode* node =
      new MediaElementAudioSourceNode(context, media_element);

  if (node) {
    media_element.SetAudioSourceNode(node);
    context.NotifySourceNodeStartedProcessing(node);
    if (!context.HasRealtimeConstraint()) {
      Deprecation::CountDeprecation(
          node->GetExecutionContext(),
          WebFeature::kMediaElementSourceOnOfflineContext);
    }
  }

  return node;
}
