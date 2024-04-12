static void limitedWithInvalidMissingDefaultAttributeAttributeGetter(const v8::PropertyCallbackInfo<v8::Value>& info)
{
    TestObjectPython* imp = V8TestObjectPython::toNative(info.Holder());
    String resultValue = imp->fastGetAttribute(HTMLNames::limitedwithinvalidmissingdefaultattributeAttr);
    if (resultValue.isEmpty()) {
        resultValue = "auto";
    } else if (equalIgnoringCase(resultValue, "ltr")) {
        resultValue = "ltr";
    } else if (equalIgnoringCase(resultValue, "rtl")) {
        resultValue = "rtl";
    } else if (equalIgnoringCase(resultValue, "auto")) {
        resultValue = "auto";
    } else {
        resultValue = "ltr";
    }
    v8SetReturnValueString(info, resultValue, info.GetIsolate());
}
