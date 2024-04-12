void ContainerNode::replaceChild(PassRefPtr<Node> newChild, Node* oldChild, ExceptionState& es)
{
    ASSERT(refCount() || parentOrShadowHostNode());

    RefPtr<Node> protect(this);

    if (oldChild == newChild) // nothing to do
        return;

    if (!oldChild) {
        es.throwUninformativeAndGenericDOMException(NotFoundError);
        return;
    }

    if (!checkReplaceChild(this, newChild.get(), oldChild, es))
        return;

    if (oldChild->parentNode() != this) {
        es.throwUninformativeAndGenericDOMException(NotFoundError);
        return;
    }

    ChildListMutationScope mutation(this);

    RefPtr<Node> next = oldChild->nextSibling();

    RefPtr<Node> removedChild = oldChild;
    removeChild(oldChild, es);
    if (es.hadException())
        return;

    if (next && (next->previousSibling() == newChild || next == newChild)) // nothing to do
        return;

    if (!checkReplaceChild(this, newChild.get(), oldChild, es))
        return;

    NodeVector targets;
    collectChildrenAndRemoveFromOldParent(newChild.get(), targets, es);
    if (es.hadException())
        return;

    if (!checkReplaceChild(this, newChild.get(), oldChild, es))
        return;

    InspectorInstrumentation::willInsertDOMNode(&document(), this);

    for (NodeVector::const_iterator it = targets.begin(); it != targets.end(); ++it) {
        Node* child = it->get();

        if (next && next->parentNode() != this)
            break;
        if (child->parentNode())
            break;

        treeScope().adoptIfNeeded(child);

        {
            NoEventDispatchAssertion assertNoEventDispatch;
            if (next)
                insertBeforeCommon(next.get(), child);
            else
                appendChildToContainer(child, this);
        }

        updateTreeAfterInsertion(this, child);
    }

    dispatchSubtreeModifiedEvent();
}
