PassRefPtr<RenderStyle> StyleResolver::styleForText(Text* textNode)
{
    ASSERT(textNode);

    NodeRenderingTraversal::ParentDetails parentDetails;
    Node* parentNode = NodeRenderingTraversal::parent(textNode, &parentDetails);
    if (!parentNode || !parentNode->renderStyle() || parentDetails.resetStyleInheritance())
        return defaultStyleForElement();
    return parentNode->renderStyle();
}
