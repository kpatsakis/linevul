void V8TestObject::ActivityLoggingAccessForIsolatedWorldsPerWorldBindingsLongAttributeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  RUNTIME_CALL_TIMER_SCOPE_DISABLED_BY_DEFAULT(info.GetIsolate(), "Blink_TestObject_activityLoggingAccessForIsolatedWorldsPerWorldBindingsLongAttribute_Getter");

  ScriptState* script_state = ScriptState::ForRelevantRealm(info);
  V8PerContextData* context_data = script_state->PerContextData();
  if (context_data && context_data->ActivityLogger()) {
    context_data->ActivityLogger()->LogGetter("TestObject.activityLoggingAccessForIsolatedWorldsPerWorldBindingsLongAttribute");
  }

  test_object_v8_internal::ActivityLoggingAccessForIsolatedWorldsPerWorldBindingsLongAttributeAttributeGetter(info);
}
