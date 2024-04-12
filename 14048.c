static inline bool isLocalFileScheme(WKStringRef scheme)
{
    return WKStringIsEqualToUTF8CStringIgnoringCase(scheme, "file");
}
