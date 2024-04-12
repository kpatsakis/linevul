static void shortAttrAttributeSetter(v8::Local<v8::Value> jsValue, const v8::PropertyCallbackInfo<void>& info)
{
    ExceptionState exceptionState(ExceptionState::SetterContext, "shortAttr", "TestObject", info.Holder(), info.GetIsolate());
    TestObject* imp = V8TestObject::toNative(info.Holder());
    V8TRYCATCH_EXCEPTION_VOID(int, cppValue, toInt16(jsValue, exceptionState), exceptionState);
    imp->setShortAttr(cppValue);
}
