void V8TestObject::CallWithScriptStateAnyAttributeAttributeSetterCallback(
    const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestObject_callWithScriptStateAnyAttribute_Setter");

  v8::Local<v8::Value> v8_value = info[0];

  test_object_v8_internal::CallWithScriptStateAnyAttributeAttributeSetter(v8_value, info);
}
