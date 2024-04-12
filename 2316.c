void V8Console::tableCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ConsoleHelper(info).reportCall(ConsoleAPIType::kTable);
}
