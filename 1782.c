static void activityLoggingGetterForAllWorldsLongAttributeAttributeGetterCallback(v8::Local<v8::String>, const v8::PropertyCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMGetter");
    V8PerContextData* contextData = V8PerContextData::from(info.GetIsolate()->GetCurrentContext());
    if (contextData && contextData->activityLogger())
        contextData->activityLogger()->log("TestObjectPython.activityLoggingGetterForAllWorldsLongAttribute", 0, 0, "Getter");
    TestObjectPythonV8Internal::activityLoggingGetterForAllWorldsLongAttributeAttributeGetter(info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}
