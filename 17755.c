static void reflectUnsignedLongAttributeAttributeGetter(const v8::PropertyCallbackInfo<v8::Value>& info)
{
    TestObjectPython* imp = V8TestObjectPython::toNative(info.Holder());
    v8SetReturnValueUnsigned(info, std::max(0, imp->getIntegralAttribute(HTMLNames::reflectunsignedlongattributeAttr)));
}
