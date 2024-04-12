void Gfx::display(Object *obj, GBool topLevel) {
  Object obj2;
  int i;

  if (obj->isArray()) {
    for (i = 0; i < obj->arrayGetLength(); ++i) {
      obj->arrayGet(i, &obj2);
      if (!obj2.isStream()) {
	error(-1, "Weird page contents");
	obj2.free();
	return;
      }
      obj2.free();
    }
  } else if (!obj->isStream()) {
    error(-1, "Weird page contents");
    return;
  }
  parser = new Parser(xref, new Lexer(xref, obj), gFalse);
  go(topLevel);
  delete parser;
  parser = NULL;
}
