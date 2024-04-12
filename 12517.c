GBool GfxResources::lookupXObject(char *name, Object *obj) {
  GfxResources *resPtr;

  for (resPtr = this; resPtr; resPtr = resPtr->next) {
    if (resPtr->xObjDict.isDict()) {
      if (!resPtr->xObjDict.dictLookup(name, obj)->isNull())
	return gTrue;
      obj->free();
    }
  }
  error(-1, "XObject '%s' is unknown", name);
  return gFalse;
}
