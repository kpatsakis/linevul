static void BooleanOrDOMStringOrUnrestrictedDoubleMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestObject* impl = V8TestObject::ToImpl(info.Holder());

  BooleanOrStringOrUnrestrictedDouble result;
  impl->booleanOrDOMStringOrUnrestrictedDoubleMethod(result);
  V8SetReturnValue(info, result);
}
