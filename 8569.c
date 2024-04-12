const Vector<IconURL>& Document::iconURLs(int iconTypesMask)
{
    m_iconURLs.clear();

    if (!head() || !(head()->children()))
        return m_iconURLs;

    RefPtr<HTMLCollection> children = head()->children();
    unsigned int length = children->length();
    for (unsigned int i = 0; i < length; ++i) {
        Node* child = children->item(i);
        if (!child->hasTagName(linkTag))
            continue;
        HTMLLinkElement* linkElement = toHTMLLinkElement(child);
        if (!(linkElement->iconType() & iconTypesMask))
            continue;
        if (linkElement->href().isEmpty())
            continue;

        IconURL newURL(linkElement->href(), linkElement->iconSizes(), linkElement->type(), linkElement->iconType());
        m_iconURLs.prepend(newURL);
    }

    return m_iconURLs;
}
