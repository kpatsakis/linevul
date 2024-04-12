void ImageResource::MultipartDataReceived(const char* bytes, size_t size) {
  DCHECK(multipart_parser_);
  Resource::AppendData(bytes, size);
}
