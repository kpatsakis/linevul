static bool isHTMLBlockElement(const Node* node)
{
    return node->hasTagName(tdTag)
        || node->hasTagName(thTag)
        || isNonTableCellHTMLBlockElement(node);
}
