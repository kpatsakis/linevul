void HTMLInputElement::setValueInternal(const String& sanitizedValue, TextFieldEventBehavior eventBehavior)
{
    m_valueIfDirty = sanitizedValue;
    m_wasModifiedByUser = eventBehavior != DispatchNoEvent;
    setNeedsValidityCheck();
}
