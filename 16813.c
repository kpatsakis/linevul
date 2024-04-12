static void methodWithUnsignedLongSequenceMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    if (UNLIKELY(info.Length() < 1)) {
        throwTypeError(ExceptionMessages::failedToExecute("methodWithUnsignedLongSequence", "TestObject", ExceptionMessages::notEnoughArguments(1, info.Length())), info.GetIsolate());
        return;
    }
    TestObject* imp = V8TestObject::toNative(info.Holder());
    V8TRYCATCH_VOID(Vector<unsigned>, unsignedLongSequence, toNativeArray<unsigned>(info[0], 1, info.GetIsolate()));
    imp->methodWithUnsignedLongSequence(unsignedLongSequence);
}
