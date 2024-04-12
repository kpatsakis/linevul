void V8TestObject::Uint8ArrayMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestObject_uint8ArrayMethod");

  test_object_v8_internal::Uint8ArrayMethodMethod(info);
}
