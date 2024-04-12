void WebKitTestResultPrinter::PrintAudioHeader() {
  DCHECK_EQ(state_, DURING_TEST);
  if (!capture_text_only_)
    *output_ << "Content-Type: audio/wav\n";
  state_ = IN_AUDIO_BLOCK;
}
