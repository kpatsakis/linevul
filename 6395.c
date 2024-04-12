int HTMLSelectElement::nextSelectableListIndex(int startIndex) const
{
    return nextValidIndex(startIndex, SkipForwards, 1);
}
