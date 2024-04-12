GBool GfxResources::lookupMarkedContentNF(char *name, Object *obj) {
  GfxResources *resPtr;

  for (resPtr = this; resPtr; resPtr = resPtr->next) {
    if (resPtr->propertiesDict.isDict()) {
      if (!resPtr->propertiesDict.dictLookupNF(name, obj)->isNull())
	return gTrue;
      obj->free();
    }
  }
  error(-1, "Marked Content '%s' is unknown", name);
  return gFalse;
}
