bool HTMLInputElement::rangeOverflow() const
{
    return willValidate() && m_inputType->rangeOverflow(value());
}
