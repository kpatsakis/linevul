void V8InjectedScriptHost::getInternalPropertiesCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    if (info.Length() < 1)
        return;
    v8::Local<v8::Array> properties;
    if (unwrapInspector(info)->debugger()->internalProperties(info.GetIsolate()->GetCurrentContext(), info[0]).ToLocal(&properties))
        info.GetReturnValue().Set(properties);
}
