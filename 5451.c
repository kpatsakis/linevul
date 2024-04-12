JsVar *jspGetConstructor(JsVar *object) {
  if (!jsvIsObject(object)) return 0;
  JsVar *proto = jsvObjectGetChild(object, JSPARSE_INHERITS_VAR, 0);
  if (jsvIsObject(proto)) {
    JsVar *constr = jsvObjectGetChild(proto, JSPARSE_CONSTRUCTOR_VAR, 0);
    if (jsvIsFunction(constr)) {
      jsvUnLock(proto);
      return constr;
    }
    jsvUnLock(constr);
  }
  jsvUnLock(proto);
  return 0;
}
