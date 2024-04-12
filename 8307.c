static void methodWithEnforceRangeInt32Method(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "methodWithEnforceRangeInt32", "TestObject", info.Holder(), info.GetIsolate());
    if (UNLIKELY(info.Length() < 1)) {
        exceptionState.throwTypeError(ExceptionMessages::notEnoughArguments(1, info.Length()));
        exceptionState.throwIfNeeded();
        return;
    }
    TestObject* imp = V8TestObject::toNative(info.Holder());
    V8TRYCATCH_EXCEPTION_VOID(int, value, toInt32(info[0], EnforceRange, exceptionState), exceptionState);
    imp->methodWithEnforceRangeInt32(value);
}
