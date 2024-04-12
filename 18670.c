static void LimitedToOnlyAttributeAttributeSetter(
    v8::Local<v8::Value> v8_value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestObject* impl = V8TestObject::ToImpl(holder);

  V0CustomElementProcessingStack::CallbackDeliveryScope delivery_scope;

  V8StringResource<> cpp_value = v8_value;
  if (!cpp_value.Prepare())
    return;

  impl->setAttribute(html_names::kLimitedtoonlyattributeAttr, cpp_value);
}
