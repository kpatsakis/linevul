static void floatAttributeAttributeSetter(v8::Local<v8::Value> jsValue, const v8::PropertyCallbackInfo<void>& info)
{
    TestObjectPython* imp = V8TestObjectPython::toNative(info.Holder());
    V8TRYCATCH_VOID(float, cppValue, static_cast<float>(jsValue->NumberValue()));
    imp->setFloatAttribute(cppValue);
}
