static void int32ArrayMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMMethod");
    TestObjectPythonV8Internal::int32ArrayMethodMethod(info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}
