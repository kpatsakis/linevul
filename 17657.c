static void overloadedMethodG2Method(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    if (UNLIKELY(info.Length() < 1)) {
        throwTypeError(ExceptionMessages::failedToExecute("overloadedMethodG", "TestObjectPython", ExceptionMessages::notEnoughArguments(1, info.Length())), info.GetIsolate());
        return;
    }
    TestObjectPython* imp = V8TestObjectPython::toNative(info.Holder());
    V8TRYCATCH_FOR_V8STRINGRESOURCE_VOID(V8StringResource<>, strictTypeCheckingStringArg, info[0]);
    imp->overloadedMethodG(strictTypeCheckingStringArg);
}
