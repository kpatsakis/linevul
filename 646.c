static VirtualKeyboardType convertStringToKeyboardType(const AtomicString& string)
{
    DEFINE_STATIC_LOCAL(AtomicString, Default, ("default"));
    DEFINE_STATIC_LOCAL(AtomicString, Url, ("url"));
    DEFINE_STATIC_LOCAL(AtomicString, Email, ("email"));
    DEFINE_STATIC_LOCAL(AtomicString, Password, ("password"));
    DEFINE_STATIC_LOCAL(AtomicString, Web, ("web"));
    DEFINE_STATIC_LOCAL(AtomicString, Number, ("number"));
    DEFINE_STATIC_LOCAL(AtomicString, Symbol, ("symbol"));
    DEFINE_STATIC_LOCAL(AtomicString, Phone, ("phone"));
    DEFINE_STATIC_LOCAL(AtomicString, Pin, ("pin"));
    DEFINE_STATIC_LOCAL(AtomicString, Hex, ("hexadecimal"));

    if (string.isEmpty())
        return VKBTypeNotSet;
    if (equalIgnoringCase(string, Default))
        return VKBTypeDefault;
    if (equalIgnoringCase(string, Url))
        return VKBTypeUrl;
    if (equalIgnoringCase(string, Email))
        return VKBTypeEmail;
    if (equalIgnoringCase(string, Password))
        return VKBTypePassword;
    if (equalIgnoringCase(string, Web))
        return VKBTypeWeb;
    if (equalIgnoringCase(string, Number))
        return VKBTypeNumPunc;
    if (equalIgnoringCase(string, Symbol))
        return VKBTypeSymbol;
    if (equalIgnoringCase(string, Phone))
        return VKBTypePhone;
    if (equalIgnoringCase(string, Pin) || equalIgnoringCase(string, Hex))
        return VKBTypePin;
    return VKBTypeNotSet;
}
