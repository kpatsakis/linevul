void MojoVideoEncodeAcceleratorService::RequestEncodingParametersChange(
    uint32_t bitrate,
    uint32_t framerate) {
  DVLOG(2) << __func__ << " bitrate=" << bitrate << " framerate=" << framerate;
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);

  if (!encoder_)
    return;
  encoder_->RequestEncodingParametersChange(bitrate, framerate);
}
