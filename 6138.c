int HTMLSelectElement::lastSelectableListIndex() const
{
    return nextValidIndex(-1, SkipForwards, INT_MAX);
}
