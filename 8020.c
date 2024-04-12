void V8Console::traceCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ConsoleHelper(info).reportCallWithDefaultArgument(ConsoleAPIType::kTrace, String16("console.trace"));
}
