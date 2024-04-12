void PepperVideoRenderer3D::OnDecodeDone(int32_t result) {
  DCHECK(decode_pending_);
  decode_pending_ = false;

  if (result != PP_OK) {
    LOG(ERROR) << "VideoDecoder::Decode() returned " << result;
    event_handler_->OnVideoDecodeError();
    return;
  }

  delete pending_packets_.front();
  pending_packets_.pop_front();

  DecodeNextPacket();
  GetNextPicture();
}
