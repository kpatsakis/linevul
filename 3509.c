void DXVAVideoDecodeAccelerator::StopOnError(
  media::VideoDecodeAccelerator::Error error) {
  DCHECK(CalledOnValidThread());

  if (client_)
    client_->NotifyError(error);
  client_ = NULL;

  if (state_ != kUninitialized) {
    Invalidate();
  }
}
