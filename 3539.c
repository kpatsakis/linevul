int HTMLSelectElement::nextValidIndex(int listIndex, SkipDirection direction, int skip) const
{
    ASSERT(direction == -1 || direction == 1);
    const Vector<HTMLElement*>& listItems = this->listItems();
    int lastGoodIndex = listIndex;
    int size = listItems.size();
    for (listIndex += direction; listIndex >= 0 && listIndex < size; listIndex += direction) {
        --skip;
        if (!listItems[listIndex]->isDisabledFormControl() && listItems[listIndex]->hasTagName(optionTag)) {
            lastGoodIndex = listIndex;
            if (skip <= 0)
                break;
        }
    }
    return lastGoodIndex;
}
