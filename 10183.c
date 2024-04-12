static bool containsVideoTags(Element* element)
{
    for (Node* node = element->firstChild(); node; node = NodeTraversal::next(node, element)) {
        if (node->hasTagName(HTMLNames::videoTag))
            return true;
    }
    return false;
}
