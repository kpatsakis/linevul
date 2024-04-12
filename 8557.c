void V8Console::dirCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ConsoleHelper(info).reportCall(ConsoleAPIType::kDir);
}
