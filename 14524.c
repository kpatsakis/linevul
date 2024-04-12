Element* HTMLDocument::activeElement()
{
    if (Element* element = treeScope().adjustedFocusedElement())
        return element;
    return body();
}
