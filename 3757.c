static void perWorldBindingsVoidMethodMethodCallbackForMainWorld(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMMethod");
    TestObjectPythonV8Internal::perWorldBindingsVoidMethodMethodForMainWorld(info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}
