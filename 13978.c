static const QualifiedName& frameOwnerURLAttributeName(const HTMLFrameOwnerElement& frameOwner)
{
    return isHTMLObjectElement(frameOwner) ? HTMLNames::dataAttr : HTMLNames::srcAttr;
}
