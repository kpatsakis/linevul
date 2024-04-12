String HTMLDocument::dir()
{
    HTMLElement* b = body();
    if (!b)
        return String();
    return b->getAttribute(dirAttr);
}
