PassRefPtr<Element> HTMLConstructionSite::createHTMLElement(AtomicHTMLToken& token)
{
    QualifiedName tagName(nullAtom, token.name(), xhtmlNamespaceURI);
    RefPtr<Element> element = HTMLElementFactory::createHTMLElement(tagName, m_document, form(), true);
    element->setAttributeMap(token.takeAtributes(), m_fragmentScriptingPermission);
    ASSERT(element->isHTMLElement());
    return element.release();
}
