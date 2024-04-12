static void collectChildrenAndRemoveFromOldParent(Node& node, NodeVector& nodes, ExceptionState& exceptionState)
{
    if (node.isDocumentFragment()) {
        DocumentFragment& fragment = toDocumentFragment(node);
        getChildNodes(fragment, nodes);
        fragment.removeChildren();
        return;
    }
    nodes.append(&node);
    if (ContainerNode* oldParent = node.parentNode())
        oldParent->removeChild(&node, exceptionState);
}
