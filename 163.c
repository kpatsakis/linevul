PassRefPtr<CDATASection> Document::createCDATASection(const String& data, ExceptionState& es)
{
    if (isHTMLDocument()) {
        es.throwUninformativeAndGenericDOMException(NotSupportedError);
        return 0;
    }
    if (data.find("]]>") != WTF::kNotFound) {
        es.throwDOMException(InvalidCharacterError, "String cannot contain ']]>' since that is the end delimiter of a CData section.");
        return 0;
    }
    return CDATASection::create(*this, data);
}
