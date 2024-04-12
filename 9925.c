static bool isStretchingColumnFlexItem(const RenderObject* flexitem)
{
    RenderObject* parent = flexitem->parent();
    if (parent->isDeprecatedFlexibleBox() && parent->style()->boxOrient() == VERTICAL && parent->style()->boxAlign() == BSTRETCH)
        return true;

    if (parent->isFlexibleBox() && parent->style()->flexWrap() == FlexNoWrap && parent->style()->isColumnFlexDirection() && columnFlexItemHasStretchAlignment(flexitem))
        return true;
    return false;
}
