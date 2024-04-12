bool hasImpliedEndTag(Element* element)
{
    return element->hasTagName(ddTag)
        || element->hasTagName(dtTag)
        || element->hasTagName(liTag)
        || element->hasTagName(optionTag)
        || element->hasTagName(optgroupTag)
        || element->hasTagName(pTag)
        || element->hasTagName(rpTag)
        || element->hasTagName(rtTag);
}
