String createMarkup(const Node* node, EChildrenOnly childrenOnly, Vector<Node*>* nodes, EAbsoluteURLs shouldResolveURLs, Vector<QualifiedName>* tagNamesToSkip)
{
    if (!node)
        return "";

    HTMLElement* deleteButtonContainerElement = 0;
    if (Frame* frame = node->document()->frame()) {
        deleteButtonContainerElement = frame->editor()->deleteButtonController()->containerElement();
        if (node->isDescendantOf(deleteButtonContainerElement))
            return "";
    }

    MarkupAccumulator accumulator(nodes, shouldResolveURLs);
    return accumulator.serializeNodes(const_cast<Node*>(node), deleteButtonContainerElement, childrenOnly, tagNamesToSkip);
}
