bool HTMLInputElement::patternMismatch() const
{
    return willValidate() && m_inputType->patternMismatch(value());
}
