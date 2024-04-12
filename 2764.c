static ReflectedXSSDisposition combineXSSProtectionHeaderAndCSP(ReflectedXSSDisposition xssProtection, ReflectedXSSDisposition reflectedXSS)
{
    ReflectedXSSDisposition result = std::max(xssProtection, reflectedXSS);

    if (result == ReflectedXSSInvalid || result == FilterReflectedXSS || result == ReflectedXSSUnset)
        return FilterReflectedXSS;

    return result;
}
