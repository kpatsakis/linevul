void HTMLElement::collectStyleForAttribute(const Attribute& attribute, StylePropertySet* style)
{
    if (attribute.name() == alignAttr) {
        if (equalIgnoringCase(attribute.value(), "middle"))
            addPropertyToAttributeStyle(style, CSSPropertyTextAlign, CSSValueCenter);
        else
            addPropertyToAttributeStyle(style, CSSPropertyTextAlign, attribute.value());
    } else if (attribute.name() == contenteditableAttr) {
        if (attribute.isEmpty() || equalIgnoringCase(attribute.value(), "true")) {
            addPropertyToAttributeStyle(style, CSSPropertyWebkitUserModify, CSSValueReadWrite);
            addPropertyToAttributeStyle(style, CSSPropertyWordWrap, CSSValueBreakWord);
            addPropertyToAttributeStyle(style, CSSPropertyWebkitNbspMode, CSSValueSpace);
            addPropertyToAttributeStyle(style, CSSPropertyWebkitLineBreak, CSSValueAfterWhiteSpace);
        } else if (equalIgnoringCase(attribute.value(), "plaintext-only")) {
            addPropertyToAttributeStyle(style, CSSPropertyWebkitUserModify, CSSValueReadWritePlaintextOnly);
            addPropertyToAttributeStyle(style, CSSPropertyWordWrap, CSSValueBreakWord);
            addPropertyToAttributeStyle(style, CSSPropertyWebkitNbspMode, CSSValueSpace);
            addPropertyToAttributeStyle(style, CSSPropertyWebkitLineBreak, CSSValueAfterWhiteSpace);
        } else if (equalIgnoringCase(attribute.value(), "false"))
            addPropertyToAttributeStyle(style, CSSPropertyWebkitUserModify, CSSValueReadOnly);
    } else if (attribute.name() == hiddenAttr) {
        addPropertyToAttributeStyle(style, CSSPropertyDisplay, CSSValueNone);
    } else if (attribute.name() == draggableAttr) {
        if (equalIgnoringCase(attribute.value(), "true")) {
            addPropertyToAttributeStyle(style, CSSPropertyWebkitUserDrag, CSSValueElement);
            addPropertyToAttributeStyle(style, CSSPropertyWebkitUserSelect, CSSValueNone);
        } else if (equalIgnoringCase(attribute.value(), "false"))
            addPropertyToAttributeStyle(style, CSSPropertyWebkitUserDrag, CSSValueNone);
    } else if (attribute.name() == dirAttr) {
        if (equalIgnoringCase(attribute.value(), "auto"))
            addPropertyToAttributeStyle(style, CSSPropertyUnicodeBidi, unicodeBidiAttributeForDirAuto(this));
        else {
            addPropertyToAttributeStyle(style, CSSPropertyDirection, attribute.value());
            if (!hasTagName(bdiTag) && !hasTagName(bdoTag) && !hasTagName(outputTag))
                addPropertyToAttributeStyle(style, CSSPropertyUnicodeBidi, CSSValueEmbed);
        }
    } else if (attribute.name().matches(XMLNames::langAttr)) {
        mapLanguageAttributeToLocale(attribute, style);
    } else if (attribute.name() == langAttr) {
        if (!fastHasAttribute(XMLNames::langAttr))
            mapLanguageAttributeToLocale(attribute, style);
    } else
        StyledElement::collectStyleForAttribute(attribute, style);
}
