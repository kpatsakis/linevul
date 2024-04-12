static void stringAttrWithSetterExceptionAttributeGetterCallback(v8::Local<v8::String>, const v8::PropertyCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMGetter");
    TestObjectV8Internal::stringAttrWithSetterExceptionAttributeGetter(info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}
