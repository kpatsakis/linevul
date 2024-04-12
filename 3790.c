static AttributeTextStyle textStyleFromMask(int64_t mask)
{
    AttributeTextStyle style;
    if (mask & COMPOSED_TEXT_ATTRIB)
        addCompositionTextStyleToAttributeTextStyle(style);

    if (mask & ACTIVE_REGION_ATTRIB)
        addActiveTextStyleToAttributeTextStyle(style);

    return style;
}
