void ImageLoader::DecodeRequest::Reject() {
  resolver_->Reject(DOMException::Create(
      kEncodingError, "The source image cannot be decoded."));
  loader_ = nullptr;
}
