bool ShadowRoot::hasInsertionPoint() const
{
    for (Node* n = firstChild(); n; n = n->traverseNextNode(this)) {
        if (isInsertionPoint(n))
            return true;
    }

    return false;
}
