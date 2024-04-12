void V8TestObject::RuntimeCallStatsCounterAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE(info.GetIsolate(), RuntimeCallStats::CounterId::kRuntimeCallStatsCounterAttribute_Getter);

  test_object_v8_internal::RuntimeCallStatsCounterAttributeAttributeGetter(info);
}
