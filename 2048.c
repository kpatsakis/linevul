V4L2JpegEncodeAccelerator::JpegBufferRecord::JpegBufferRecord()
    : at_device(false) {
  memset(address, 0, sizeof(address));
  memset(length, 0, sizeof(length));
}
