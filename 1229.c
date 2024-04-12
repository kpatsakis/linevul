bool HTMLAnchorElement::isLiveLink() const
{
    return isLink() && !hasEditableStyle();
}
