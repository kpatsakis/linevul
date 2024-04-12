protocol::VideoStub* PepperVideoRenderer2D::GetVideoStub() {
  DCHECK(CalledOnValidThread());

  return software_video_renderer_->GetVideoStub();
}
