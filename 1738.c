static void strictFunctionMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "strictFunction", "TestObject", info.Holder(), info.GetIsolate());
    if (UNLIKELY(info.Length() < 3)) {
        exceptionState.throwTypeError(ExceptionMessages::notEnoughArguments(3, info.Length()));
        exceptionState.throwIfNeeded();
        return;
    }
    TestObject* imp = V8TestObject::toNative(info.Holder());
    V8TRYCATCH_FOR_V8STRINGRESOURCE_VOID(V8StringResource<>, str, info[0]);
    V8TRYCATCH_VOID(float, a, static_cast<float>(info[1]->NumberValue()));
    V8TRYCATCH_EXCEPTION_VOID(int, b, toInt32(info[2], exceptionState), exceptionState);
    bool result = imp->strictFunction(str, a, b, exceptionState);
    if (exceptionState.throwIfNeeded())
        return;
    v8SetReturnValueBool(info, result);
}
