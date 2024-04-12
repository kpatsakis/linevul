int DCTStream::lookChar() {
  if (y >= height) {
    return EOF;
  }
  if (progressive || !interleaved) {
    return frameBuf[comp][y * bufWidth + x];
  } else {
    if (dy >= mcuHeight) {
      if (!readMCURow()) {
	y = height;
	return EOF;
      }
      comp = 0;
      x = 0;
      dy = 0;
    }
    return rowBuf[comp][dy][x];
  }
}
