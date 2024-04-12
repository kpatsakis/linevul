void ScriptProcessorHandler::SetChannelCount(unsigned long channel_count,
                                             ExceptionState& exception_state) {
  DCHECK(IsMainThread());
  BaseAudioContext::GraphAutoLocker locker(Context());

  if (channel_count != channel_count_) {
    exception_state.ThrowDOMException(
        kNotSupportedError, "channelCount cannot be changed from " +
                                String::Number(channel_count_) + " to " +
                                String::Number(channel_count));
  }
}
