void HTMLConstructionSite::insertHTMLHtmlStartTagBeforeHTML(AtomicHTMLToken& token)
{
    RefPtr<Element> element = HTMLHtmlElement::create(m_document);
    element->setAttributeMap(token.takeAtributes(), m_fragmentScriptingPermission);
    m_openElements.pushHTMLHtmlElement(attach(m_document, element.release()));
    dispatchDocumentElementAvailableIfNeeded();
}
