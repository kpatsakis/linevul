void BaseMultipleFieldsDateAndTimeInputType::valueAttributeChanged()
{
    if (!element()->hasDirtyValue())
        updateInnerTextValue();
}
