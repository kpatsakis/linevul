static void handleMetaNameAttribute(const Token& token, CachedDocumentParameters* documentParameters, MediaValuesCached* mediaValues, CSSPreloadScanner* cssScanner, ViewportDescriptionWrapper* viewport)
{
    const typename Token::Attribute* nameAttribute = token.getAttributeItem(nameAttr);
    if (!nameAttribute)
        return;

    String nameAttributeValue(nameAttribute->value());
    const typename Token::Attribute* contentAttribute = token.getAttributeItem(contentAttr);
    if (!contentAttribute)
        return;

    String contentAttributeValue(contentAttribute->value());
    if (equalIgnoringCase(nameAttributeValue, "viewport")) {
        handleMetaViewport(contentAttributeValue, documentParameters, mediaValues, viewport);
        return;
    }

    if (equalIgnoringCase(nameAttributeValue, "referrer")) {
        handleMetaReferrer(contentAttributeValue, documentParameters, cssScanner);
    }
}
