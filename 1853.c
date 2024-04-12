static void stringArrayFunctionMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "stringArrayFunction", "TestObject", info.Holder(), info.GetIsolate());
    if (UNLIKELY(info.Length() < 1)) {
        exceptionState.throwTypeError(ExceptionMessages::notEnoughArguments(1, info.Length()));
        exceptionState.throwIfNeeded();
        return;
    }
    TestObject* imp = V8TestObject::toNative(info.Holder());
    V8TRYCATCH_VOID(Vector<String>, values, toNativeArray<String>(info[0], 1, info.GetIsolate()));
    Vector<String> result = imp->stringArrayFunction(values, exceptionState);
    if (exceptionState.throwIfNeeded())
        return;
    v8SetReturnValue(info, v8Array(result, info.GetIsolate()));
}
