static void activityLoggingAccessPerWorldBindingsLongAttributeAttributeSetterForMainWorld(v8::Local<v8::Value> jsValue, const v8::PropertyCallbackInfo<void>& info)
{
    ExceptionState exceptionState(ExceptionState::SetterContext, "activityLoggingAccessPerWorldBindingsLongAttribute", "TestObjectPython", info.Holder(), info.GetIsolate());
    TestObjectPython* imp = V8TestObjectPython::toNative(info.Holder());
    V8TRYCATCH_EXCEPTION_VOID(int, cppValue, toInt32(jsValue, exceptionState), exceptionState);
    imp->setActivityLoggingAccessPerWorldBindingsLongAttribute(cppValue);
}
