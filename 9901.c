void MojoVideoEncodeAcceleratorService::Encode(
    const scoped_refptr<VideoFrame>& frame,
    bool force_keyframe,
    EncodeCallback callback) {
  DVLOG(2) << __func__ << " tstamp=" << frame->timestamp();
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
  if (!encoder_)
    return;

  if (frame->coded_size() != input_coded_size_) {
    DLOG(ERROR) << __func__ << " wrong input coded size, expected "
                << input_coded_size_.ToString() << ", got "
                << frame->coded_size().ToString();
    NotifyError(::media::VideoEncodeAccelerator::kInvalidArgumentError);
    std::move(callback).Run();
    return;
  }

  frame->AddDestructionObserver(media::BindToCurrentLoop(std::move(callback)));
  encoder_->Encode(frame, force_keyframe);
}
