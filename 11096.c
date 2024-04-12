void AudioNode::setChannelCountMode(const String& mode,
                                    ExceptionState& exception_state) {
  Handler().SetChannelCountMode(mode, exception_state);
}
