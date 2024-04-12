static bool semicolonSeparatedValueContainsJavaScriptURL(const String& value)
{
    Vector<String> valueList;
    value.split(';', valueList);
    for (size_t i = 0; i < valueList.size(); ++i) {
        if (protocolIsJavaScript(valueList[i]))
            return true;
    }
    return false;
}
