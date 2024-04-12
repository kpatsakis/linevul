bool HTMLSelectElement::valueMissing() const
{
    if (!willValidate())
        return false;

    if (!isRequired())
        return false;

    int firstSelectionIndex = selectedIndex();

    return firstSelectionIndex < 0 || (!firstSelectionIndex && hasPlaceholderLabelOption());
}
