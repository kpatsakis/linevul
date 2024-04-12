static bool isSetCookieHeader(const AtomicString& name)
{
    return equalIgnoringCase(name, "set-cookie") || equalIgnoringCase(name, "set-cookie2");
}
