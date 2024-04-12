GfxFont *GfxResources::lookupFont(char *name) {
  GfxFont *font;
  GfxResources *resPtr;

  for (resPtr = this; resPtr; resPtr = resPtr->next) {
    if (resPtr->fonts) {
      if ((font = resPtr->fonts->lookup(name)))
	return font;
    }
  }
  error(-1, "Unknown font tag '%s'", name);
  return NULL;
}
