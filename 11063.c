static void CachedAttributeRaisesExceptionGetterAnyAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestObject* impl = V8TestObject::ToImpl(holder);

  V8PrivateProperty::Symbol property_symbol =
      V8PrivateProperty::GetSymbol(info.GetIsolate(),
          kPrivatePropertyCachedAttributeRaisesExceptionGetterAnyAttribute);
  if (!static_cast<const TestObject*>(impl)->isValueDirty()) {
    v8::Local<v8::Value> v8_value;
    if (property_symbol.GetOrUndefined(holder).ToLocal(&v8_value) && !v8_value->IsUndefined()) {
      V8SetReturnValue(info, v8_value);
      return;
    }
  }

  ExceptionState exception_state(info.GetIsolate(), ExceptionState::kGetterContext, "TestObject", "cachedAttributeRaisesExceptionGetterAnyAttribute");

  ScriptValue cpp_value(impl->cachedAttributeRaisesExceptionGetterAnyAttribute(exception_state));

  if (UNLIKELY(exception_state.HadException()))
    return;

  v8::Local<v8::Value> v8_value(cpp_value.V8Value());
  property_symbol.Set(holder, v8_value);

  V8SetReturnValue(info, v8_value);
}
