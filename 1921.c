void Document::childrenChanged(bool changedByParser, Node* beforeChange, Node* afterChange, int childCountDelta)
{
    ContainerNode::childrenChanged(changedByParser, beforeChange, afterChange, childCountDelta);
    
    Element* newDocumentElement = ElementTraversal::firstWithin(this);
    if (newDocumentElement == m_documentElement)
        return;
    m_documentElement = newDocumentElement;
    clearStyleResolver();
}
