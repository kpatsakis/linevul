static void overloadedPerWorldMethod1MethodForMainWorld(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "overloadedPerWorldMethod", "TestObject", info.Holder(), info.GetIsolate());
    if (UNLIKELY(info.Length() < 1)) {
        exceptionState.throwTypeError(ExceptionMessages::notEnoughArguments(1, info.Length()));
        exceptionState.throwIfNeeded();
        return;
    }
    TestObject* imp = V8TestObject::toNative(info.Holder());
    V8TRYCATCH_EXCEPTION_VOID(int, longArg, toInt32(info[0], exceptionState), exceptionState);
    imp->overloadedPerWorldMethod(longArg);
}
