PassRefPtr<Attr> Document::createAttributeNS(const String& namespaceURI, const String& qualifiedName, ExceptionState& es, bool shouldIgnoreNamespaceChecks)
{
    String prefix, localName;
    if (!parseQualifiedName(qualifiedName, prefix, localName, es))
        return 0;

    QualifiedName qName(prefix, localName, namespaceURI);

    if (!shouldIgnoreNamespaceChecks && !hasValidNamespaceForAttributes(qName)) {
        es.throwUninformativeAndGenericDOMException(NamespaceError);
        return 0;
    }

    return Attr::create(*this, qName, emptyString());
}
