bool RenderFlexibleBox::hasAutoMarginsInCrossAxis(RenderBox* child) const
{
    if (isHorizontalFlow())
        return child->style()->marginTop().isAuto() || child->style()->marginBottom().isAuto();
    return child->style()->marginLeft().isAuto() || child->style()->marginRight().isAuto();
}
