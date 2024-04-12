void ContainerNode::setHovered(bool over)
{
    if (over == hovered()) return;

    Node::setHovered(over);

    if (!renderer()) {
        if (!over)
            setNeedsStyleRecalc();

        return;
    }

    if (renderer()) {
        if (renderStyle()->affectedByHover() || (isElementNode() && toElement(this)->childrenAffectedByHover()))
            setNeedsStyleRecalc();
        if (renderer() && renderer()->style()->hasAppearance())
            RenderTheme::theme().stateChanged(renderer(), HoverState);
    }
}
