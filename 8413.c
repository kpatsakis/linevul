 vpx_codec_err_t DecodeRemainingFrames() {
 for (; video_->cxdata() != NULL; video_->Next()) {
 const vpx_codec_err_t res =
          decoder_->DecodeFrame(video_->cxdata(), video_->frame_size());
 if (res != VPX_CODEC_OK)
 return res;
 CheckDecodedFrames();
 }
 return VPX_CODEC_OK;
 }
