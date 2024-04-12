String Document::webkitVisibilityState() const
{
    return pageVisibilityStateString(visibilityState());
}
