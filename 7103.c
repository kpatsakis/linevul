JsvIsInternalChecker jsvGetInternalFunctionCheckerFor(JsVar *v) {
  if (jsvIsFunction(v)) return jsvIsInternalFunctionKey;
  if (jsvIsObject(v)) return jsvIsInternalObjectKey;
  return 0;
}
