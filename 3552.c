PassRefPtr<NodeList> Document::handleZeroPadding(const HitTestRequest& request, HitTestResult& result) const
{
    renderView()->hitTest(request, result);

    Node* node = result.innerNode();
    if (!node)
        return 0;

    node = node->deprecatedShadowAncestorNode();
    ListHashSet<RefPtr<Node> > list;
    list.add(node);
    return StaticHashSetNodeList::adopt(list);
}
