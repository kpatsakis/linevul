Goffset JBIG2Stream::getPos() {
  if (pageBitmap == NULL) {
    return 0;
  }
  return dataPtr - pageBitmap->getDataPtr();
}
