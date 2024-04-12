void HTMLConstructionSite::insertHTMLHtmlStartTagInBody(AtomicHTMLToken& token)
{
    mergeAttributesFromTokenIntoElement(token, m_openElements.htmlElement());
}
