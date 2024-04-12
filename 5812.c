static void ReadonlyEventTargetAttributeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestObject* impl = V8TestObject::ToImpl(holder);

  V8SetReturnValueFast(info, WTF::GetPtr(impl->readonlyEventTargetAttribute()), impl);
}
