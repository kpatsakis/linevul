ValidityState* FormAssociatedElement::validity()
{
    if (!m_validityState)
        m_validityState = ValidityState::create(this);

    return m_validityState.get();
}
