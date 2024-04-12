void V8Console::groupEndCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ConsoleHelper(info).reportCallWithDefaultArgument(ConsoleAPIType::kEndGroup, String16("console.groupEnd"));
}
