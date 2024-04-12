uint64_t HTMLMediaElement::webkitVideoDecodedByteCount() const {
  if (!GetWebMediaPlayer())
    return 0;
  return GetWebMediaPlayer()->VideoDecodedByteCount();
}
