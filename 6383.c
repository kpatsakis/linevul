void Document::setXMLStandalone(bool standalone, ExceptionState& es)
{
    if (!implementation()->hasFeature("XML", String())) {
        es.throwUninformativeAndGenericDOMException(NotSupportedError);
        return;
    }

    m_xmlStandalone = standalone ? Standalone : NotStandalone;
}
