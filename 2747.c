static void readonlyDOMTimeStampAttributeAttributeGetter(const v8::PropertyCallbackInfo<v8::Value>& info)
{
    TestObjectPython* imp = V8TestObjectPython::toNative(info.Holder());
    v8SetReturnValue(info, static_cast<double>(imp->readonlyDOMTimeStampAttribute()));
}
