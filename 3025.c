static void ReflectUnsignedShortAttributeAttributeSetter(
    v8::Local<v8::Value> v8_value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestObject* impl = V8TestObject::ToImpl(holder);

  V0CustomElementProcessingStack::CallbackDeliveryScope delivery_scope;

  ExceptionState exception_state(isolate, ExceptionState::kSetterContext, "TestObject", "reflectUnsignedShortAttribute");

  uint16_t cpp_value = NativeValueTraits<IDLUnsignedShort>::NativeValue(info.GetIsolate(), v8_value, exception_state);
  if (exception_state.HadException())
    return;

  impl->setAttribute(html_names::kReflectunsignedshortattributeAttr, cpp_value);
}
