Encoder* ScreenRecorder::encoder() {
  DCHECK_EQ(encode_loop_, MessageLoop::current());
  DCHECK(encoder_.get());
  return encoder_.get();
}
