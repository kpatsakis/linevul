void V8TestObject::CallWithThisValueMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestObject_callWithThisValue");

  test_object_v8_internal::CallWithThisValueMethod(info);
}
