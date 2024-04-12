static void voidMethodUnsignedLongLongArgMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "voidMethodUnsignedLongLongArg", "TestObjectPython", info.Holder(), info.GetIsolate());
    if (UNLIKELY(info.Length() < 1)) {
        exceptionState.throwTypeError(ExceptionMessages::notEnoughArguments(1, info.Length()));
        exceptionState.throwIfNeeded();
        return;
    }
    TestObjectPython* imp = V8TestObjectPython::toNative(info.Holder());
    V8TRYCATCH_EXCEPTION_VOID(unsigned long long, unsignedLongLongArg, toUInt64(info[0], exceptionState), exceptionState);
    imp->voidMethodUnsignedLongLongArg(unsignedLongLongArg);
}
