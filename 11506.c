static void voidMethodLongArgTestInterfaceEmptyArgMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "voidMethodLongArgTestInterfaceEmptyArg", "TestObjectPython", info.Holder(), info.GetIsolate());
    if (UNLIKELY(info.Length() < 2)) {
        exceptionState.throwTypeError(ExceptionMessages::notEnoughArguments(2, info.Length()));
        exceptionState.throwIfNeeded();
        return;
    }
    TestObjectPython* imp = V8TestObjectPython::toNative(info.Holder());
    V8TRYCATCH_EXCEPTION_VOID(int, longArg, toInt32(info[0], exceptionState), exceptionState);
    V8TRYCATCH_VOID(TestInterfaceEmpty*, testInterfaceEmptyArg, V8TestInterfaceEmpty::toNativeWithTypeCheck(info.GetIsolate(), info[1]));
    imp->voidMethodLongArgTestInterfaceEmptyArg(longArg, testInterfaceEmptyArg);
}
