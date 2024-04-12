static void voidMethodLongArgOptionalTestInterfaceEmptyArgMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "voidMethodLongArgOptionalTestInterfaceEmptyArg", "TestObjectPython", info.Holder(), info.GetIsolate());
    if (UNLIKELY(info.Length() < 1)) {
        exceptionState.throwTypeError(ExceptionMessages::notEnoughArguments(1, info.Length()));
        exceptionState.throwIfNeeded();
        return;
    }
    TestObjectPython* imp = V8TestObjectPython::toNative(info.Holder());
    V8TRYCATCH_EXCEPTION_VOID(int, longArg, toInt32(info[0], exceptionState), exceptionState);
    if (UNLIKELY(info.Length() <= 1)) {
        imp->voidMethodLongArgOptionalTestInterfaceEmptyArg(longArg);
        return;
    }
    V8TRYCATCH_VOID(TestInterfaceEmpty*, optionalTestInterfaceEmpty, V8TestInterfaceEmpty::toNativeWithTypeCheck(info.GetIsolate(), info[1]));
    imp->voidMethodLongArgOptionalTestInterfaceEmptyArg(longArg, optionalTestInterfaceEmpty);
}
