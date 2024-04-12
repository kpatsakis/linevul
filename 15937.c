bool supportsInvalidation(CSSSelector::Match match)
{
    switch (match) {
    case CSSSelector::Tag:
    case CSSSelector::Id:
    case CSSSelector::Class:
    case CSSSelector::AttributeExact:
    case CSSSelector::AttributeSet:
    case CSSSelector::AttributeHyphen:
    case CSSSelector::AttributeList:
    case CSSSelector::AttributeContain:
    case CSSSelector::AttributeBegin:
    case CSSSelector::AttributeEnd:
        return true;
    case CSSSelector::Unknown:
    case CSSSelector::PagePseudoClass:
        ASSERT_NOT_REACHED();
        return false;
    default:
        ASSERT_NOT_REACHED();
        return false;
    }
}
