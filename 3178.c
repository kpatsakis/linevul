long long jsvGetLongIntegerAndUnLock(JsVar *v) {
  long long i = jsvGetLongInteger(v);
  jsvUnLock(v);
  return i;
}
