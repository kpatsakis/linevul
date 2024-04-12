void Document::processBaseElement()
{
    const AtomicString* href = 0;
    const AtomicString* target = 0;
    for (Element* element = ElementTraversal::firstWithin(this); element && (!href || !target); element = ElementTraversal::next(element)) {
        if (element->hasTagName(baseTag)) {
            if (!href) {
                const AtomicString& value = element->fastGetAttribute(hrefAttr);
                if (!value.isNull())
                    href = &value;
            }
            if (!target) {
                const AtomicString& value = element->fastGetAttribute(targetAttr);
                if (!value.isNull())
                    target = &value;
            }
            if (contentSecurityPolicy()->isActive())
                UseCounter::count(*this, UseCounter::ContentSecurityPolicyWithBaseElement);
        }
    }

    KURL baseElementURL;
    if (href) {
        String strippedHref = stripLeadingAndTrailingHTMLSpaces(*href);
        if (!strippedHref.isEmpty())
            baseElementURL = KURL(url(), strippedHref);
    }
    if (m_baseElementURL != baseElementURL && contentSecurityPolicy()->allowBaseURI(baseElementURL)) {
        m_baseElementURL = baseElementURL;
        updateBaseURL();
    }

    m_baseTarget = target ? *target : nullAtom;
}
