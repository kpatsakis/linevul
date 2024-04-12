void V8Console::timeCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    timeFunction(info, false);
}
