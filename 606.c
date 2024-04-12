void BaseMultipleFieldsDateAndTimeInputType::updateClearButtonVisibility()
{
    ClearButtonElement* clearButton = clearButtonElement();
    if (!clearButton)
        return;

    if (element()->isRequired() || !dateTimeEditElement()->anyEditableFieldsHaveValues())
        clearButton->setInlineStyleProperty(CSSPropertyVisibility, CSSValueHidden);
    else
        clearButton->removeInlineStyleProperty(CSSPropertyVisibility);
}
