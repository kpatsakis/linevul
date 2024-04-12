void ScreenRecorder::DoStopOnEncodeThread(const base::Closure& done_task) {
  DCHECK_EQ(encode_loop_, MessageLoop::current());

  encoder_stopped_ = true;

  capture_loop_->PostTask(FROM_HERE, done_task);
}
