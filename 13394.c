static void SetterCallWithExecutionContextStringAttributeAttributeSetter(
    v8::Local<v8::Value> v8_value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  ALLOW_UNUSED_LOCAL(isolate);

  v8::Local<v8::Object> holder = info.Holder();
  ALLOW_UNUSED_LOCAL(holder);

  TestObject* impl = V8TestObject::ToImpl(holder);

  V8StringResource<> cpp_value = v8_value;
  if (!cpp_value.Prepare())
    return;

  ExecutionContext* execution_context = ExecutionContext::ForRelevantRealm(info);

  impl->setSetterCallWithExecutionContextStringAttribute(execution_context, cpp_value);
}
