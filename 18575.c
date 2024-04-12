void V8TestObject::VoidMethodArrayBufferOrArrayBufferViewOrDictionaryArgMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestObject_voidMethodArrayBufferOrArrayBufferViewOrDictionaryArg");

  test_object_v8_internal::VoidMethodArrayBufferOrArrayBufferViewOrDictionaryArgMethod(info);
}
