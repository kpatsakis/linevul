KURL Document::openSearchDescriptionURL()
{
    static const char* const openSearchMIMEType = "application/opensearchdescription+xml";
    static const char* const openSearchRelation = "search";

    if (!frame() || frame()->tree()->parent())
        return KURL();

    if (frame()->loader()->state() != FrameStateComplete)
        return KURL();

    if (!head())
        return KURL();

    RefPtr<HTMLCollection> children = head()->children();
    for (unsigned i = 0; Node* child = children->item(i); i++) {
        if (!child->hasTagName(linkTag))
            continue;
        HTMLLinkElement* linkElement = static_cast<HTMLLinkElement*>(child);
        if (!equalIgnoringCase(linkElement->type(), openSearchMIMEType) || !equalIgnoringCase(linkElement->rel(), openSearchRelation))
            continue;
        if (linkElement->href().isEmpty())
            continue;
        return linkElement->href();
    }

    return KURL();
}
