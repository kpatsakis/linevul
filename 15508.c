static void raisesExceptionGetterLongAttributeAttributeGetter(const v8::PropertyCallbackInfo<v8::Value>& info)
{
    TestObjectPython* imp = V8TestObjectPython::toNative(info.Holder());
    ExceptionState exceptionState(ExceptionState::GetterContext, "raisesExceptionGetterLongAttribute", "TestObjectPython", info.Holder(), info.GetIsolate());
    int jsValue = imp->raisesExceptionGetterLongAttribute(exceptionState);
    if (UNLIKELY(exceptionState.throwIfNeeded()))
        return;
    v8SetReturnValueInt(info, jsValue);
}
