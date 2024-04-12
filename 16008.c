void HTMLInputElement::subtreeHasChanged()
{
    m_inputType->subtreeHasChanged();
    calculateAndAdjustDirectionality();
}
