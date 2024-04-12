static void float32ArrayMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TestObjectPython* imp = V8TestObjectPython::toNative(info.Holder());
    v8SetReturnValue(info, imp->float32ArrayMethod());
}
