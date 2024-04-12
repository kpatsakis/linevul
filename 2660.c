String HTMLInputElement::localizeValue(const String& proposedValue) const
{
    if (proposedValue.isNull())
        return proposedValue;
    return m_inputType->localizeValue(proposedValue);
}
