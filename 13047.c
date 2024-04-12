PassRefPtrWillBeRawPtr<Node> ContainerNode::replaceChild(PassRefPtrWillBeRawPtr<Node> newChild, PassRefPtrWillBeRawPtr<Node> oldChild, ExceptionState& exceptionState)
{
#if !ENABLE(OILPAN)
    ASSERT(refCount() || parentOrShadowHostNode());
#endif

    RefPtrWillBeRawPtr<Node> protect(this);

    if (oldChild == newChild) // Nothing to do.
        return oldChild;

    if (!oldChild) {
        exceptionState.throwDOMException(NotFoundError, "The node to be replaced is null.");
        return nullptr;
    }

    RefPtrWillBeRawPtr<Node> child = oldChild;

    if (!checkAcceptChild(newChild.get(), child.get(), exceptionState)) {
        if (exceptionState.hadException())
            return nullptr;
        return child;
    }

    if (child->parentNode() != this) {
        exceptionState.throwDOMException(NotFoundError, "The node to be replaced is not a child of this node.");
        return nullptr;
    }

    ChildListMutationScope mutation(*this);

    RefPtrWillBeRawPtr<Node> next = child->nextSibling();

    removeChild(child, exceptionState);
    if (exceptionState.hadException())
        return nullptr;

    if (next && (next->previousSibling() == newChild || next == newChild)) // nothing to do
        return child;

    if (!checkAcceptChild(newChild.get(), child.get(), exceptionState)) {
        if (exceptionState.hadException())
            return nullptr;
        return child;
    }

    NodeVector targets;
    collectChildrenAndRemoveFromOldParent(*newChild, targets, exceptionState);
    if (exceptionState.hadException())
        return nullptr;

    if (!checkAcceptChild(newChild.get(), child.get(), exceptionState)) {
        if (exceptionState.hadException())
            return nullptr;
        return child;
    }

    InspectorInstrumentation::willInsertDOMNode(this);

    for (const auto& targetNode : targets) {
        ASSERT(targetNode);
        Node& child = *targetNode;

        if (next && next->parentNode() != this)
            break;
        if (child.parentNode())
            break;

        treeScope().adoptIfNeeded(child);

        {
            EventDispatchForbiddenScope assertNoEventDispatch;
            if (next)
                insertBeforeCommon(*next, child);
            else
                appendChildCommon(child);
        }

        updateTreeAfterInsertion(child);
    }

    dispatchSubtreeModifiedEvent();
    return child;
}
