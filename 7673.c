static void idAttributeSetterCallback(v8::Local<v8::String>, v8::Local<v8::Value> jsValue, const v8::PropertyCallbackInfo<void>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMSetter");
    CustomElementCallbackDispatcher::CallbackDeliveryScope deliveryScope;
    TestObjectPythonV8Internal::idAttributeSetter(jsValue, info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}
