static void nullableStringAttributeAttributeGetter(const v8::PropertyCallbackInfo<v8::Value>& info)
{
    TestObjectPython* imp = V8TestObjectPython::toNative(info.Holder());
    bool isNull = false;
    String jsValue = imp->nullableStringAttribute(isNull);
    if (isNull) {
        v8SetReturnValueNull(info);
        return;
    }
    v8SetReturnValueString(info, jsValue, info.GetIsolate());
}
