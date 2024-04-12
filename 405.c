bool IsVoiceInteractionEnabled() {
  return IsVoiceInteractionLocalesSupported() &&
         IsVoiceInteractionFlagsEnabled();
}
