static bool isCharsetSpecifyingNode(Node* node)
{
    if (!node->isHTMLElement())
        return false;

    HTMLElement* element = toHTMLElement(node);
    if (!element->hasTagName(HTMLNames::metaTag))
        return false;
    HTMLMetaCharsetParser::AttributeList attributes;
    if (element->hasAttributes()) {
        for (unsigned i = 0; i < element->attributeCount(); ++i) {
            const Attribute* attribute = element->attributeItem(i);
            attributes.append(std::make_pair(attribute->name().toString(), attribute->value().string()));
        }
    }
    WTF::TextEncoding textEncoding = HTMLMetaCharsetParser::encodingFromMetaAttributes(attributes);
    return textEncoding.isValid();
}
