static void treatNullAsNullStringStringAttributeAttributeSetter(v8::Local<v8::Value> jsValue, const v8::PropertyCallbackInfo<void>& info)
{
    TestObjectPython* imp = V8TestObjectPython::toNative(info.Holder());
    V8TRYCATCH_FOR_V8STRINGRESOURCE_VOID(V8StringResource<WithNullCheck>, cppValue, jsValue);
    imp->setTreatNullAsNullStringStringAttribute(cppValue);
}
