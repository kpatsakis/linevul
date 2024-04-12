bool WebPage::nodeHasHover(const WebDOMNode& node)
{
    if (Node* nodeImpl = node.impl()) {
        if (RenderStyle* style = nodeImpl->renderStyle())
            return style->affectedByHoverRules();
    }
    return false;
}
