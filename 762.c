static void activityLoggedInIsolatedWorldsAttrSetterAttributeSetterCallbackForMainWorld(v8::Local<v8::String>, v8::Local<v8::Value> jsValue, const v8::PropertyCallbackInfo<void>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMSetter");
    TestObjectV8Internal::activityLoggedInIsolatedWorldsAttrSetterAttributeSetterForMainWorld(jsValue, info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}
