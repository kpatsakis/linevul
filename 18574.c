void ScreenRecorder::DoStart() {
  DCHECK_EQ(capture_loop_, MessageLoop::current());

  if (is_recording_) {
    NOTREACHED() << "Record session already started.";
    return;
  }

  is_recording_ = true;

  DoCapture();
}
