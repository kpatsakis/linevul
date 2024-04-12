static void raisesExceptionVoidMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "raisesExceptionVoidMethod", "TestObjectPython", info.Holder(), info.GetIsolate());
    TestObjectPython* imp = V8TestObjectPython::toNative(info.Holder());
    imp->raisesExceptionVoidMethod(exceptionState);
    if (exceptionState.throwIfNeeded())
        return;
}
