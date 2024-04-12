void FoFiType1C::eexecCvtGlyph(Type1CEexecBuf *eb, const char *glyphName,
			       int offset, int nBytes,
			       Type1CIndex *subrIdx,
			       Type1CPrivateDict *pDict) {
  GooString *buf;
  GooString *charBuf;

  charBuf = new GooString();
  cvtGlyph(offset, nBytes, charBuf, subrIdx, pDict, gTrue);

  buf = GooString::format("/{0:s} {1:d} RD ", glyphName, charBuf->getLength());
  eexecWrite(eb, buf->getCString());
  delete buf;
  eexecWriteCharstring(eb, (Guchar *)charBuf->getCString(),
		       charBuf->getLength());
  eexecWrite(eb, " ND\n");

  delete charBuf;
}
