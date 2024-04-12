bool ContainerNode::checkAcceptChild(const Node* newChild, const Node* oldChild, ExceptionState& exceptionState) const
{
    if (!newChild) {
        exceptionState.throwDOMException(NotFoundError, "The new child element is null.");
        return false;
    }

    if ((newChild->isElementNode() || newChild->isTextNode()) && isElementNode()) {
        ASSERT(isChildTypeAllowed(*newChild));
        if (containsConsideringHostElements(*newChild)) {
            exceptionState.throwDOMException(HierarchyRequestError, "The new child element contains the parent.");
            return false;
        }
        return true;
    }

    ASSERT(!newChild->isPseudoElement());
    if (newChild->isPseudoElement()) {
        exceptionState.throwDOMException(HierarchyRequestError, "The new child element is a pseudo-element.");
        return false;
    }

    return checkAcceptChildGuaranteedNodeTypes(*newChild, oldChild, exceptionState);
}
