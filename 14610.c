void AudioNode::disconnect(AudioParam* destination_param,
                           ExceptionState& exception_state) {
  DCHECK(IsMainThread());
  BaseAudioContext::GraphAutoLocker locker(context());

  unsigned number_of_disconnections = 0;

  for (unsigned output_index = 0; output_index < Handler().NumberOfOutputs();
       ++output_index) {
    if (DisconnectFromOutputIfConnected(output_index, *destination_param))
      number_of_disconnections++;
  }

  if (number_of_disconnections == 0) {
    exception_state.ThrowDOMException(kInvalidAccessError,
                                      "the given AudioParam is not connected.");
    return;
  }
}
