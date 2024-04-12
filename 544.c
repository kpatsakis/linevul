GfxColorSpace *GfxCalGrayColorSpace::copy() {
  GfxCalGrayColorSpace *cs;

  cs = new GfxCalGrayColorSpace();
  cs->whiteX = whiteX;
  cs->whiteY = whiteY;
  cs->whiteZ = whiteZ;
  cs->blackX = blackX;
  cs->blackY = blackY;
  cs->blackZ = blackZ;
  cs->gamma = gamma;
  return cs;
}
