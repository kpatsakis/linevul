static void enforcedRangeByteAttrAttributeSetter(v8::Local<v8::Value> jsValue, const v8::PropertyCallbackInfo<void>& info)
{
    ExceptionState exceptionState(ExceptionState::SetterContext, "enforcedRangeByteAttr", "TestObject", info.Holder(), info.GetIsolate());
    TestObject* imp = V8TestObject::toNative(info.Holder());
    V8TRYCATCH_EXCEPTION_VOID(int, cppValue, toInt8(jsValue, EnforceRange, exceptionState), exceptionState);
    imp->setEnforcedRangeByteAttr(cppValue);
}
