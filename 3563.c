VideoCaptureImpl::~VideoCaptureImpl() {
  DCHECK(io_thread_checker_.CalledOnValidThread());
  if ((state_ == VIDEO_CAPTURE_STATE_STARTING ||
       state_ == VIDEO_CAPTURE_STATE_STARTED) &&
      GetVideoCaptureHost())
    GetVideoCaptureHost()->Stop(device_id_);
}
