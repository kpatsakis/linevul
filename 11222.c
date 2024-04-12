static void assertLayoutTreeUpdated(Node& root)
{
    for (Node& node : NodeTraversal::inclusiveDescendantsOf(root)) {
        if (!node.isElementNode()
            && !node.isTextNode()
            && !node.isShadowRoot()
            && !node.isDocumentNode())
            continue;
        DCHECK(!node.needsStyleRecalc());
        DCHECK(!node.childNeedsStyleRecalc());
        DCHECK(!node.childNeedsDistributionRecalc());
        DCHECK(!node.needsStyleInvalidation());
        DCHECK(!node.childNeedsStyleInvalidation());
        for (ShadowRoot* shadowRoot = node.youngestShadowRoot(); shadowRoot; shadowRoot = shadowRoot->olderShadowRoot())
            assertLayoutTreeUpdated(*shadowRoot);
    }
}
