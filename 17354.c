void BaseMultipleFieldsDateAndTimeInputType::restoreFormControlState(const FormControlState& state)
{
    if (!m_dateTimeEditElement)
        return;
    DateTimeFieldsState dateTimeFieldsState = DateTimeFieldsState::restoreFormControlState(state);
    m_dateTimeEditElement->setValueAsDateTimeFieldsState(dateTimeFieldsState);
    element()->setValueInternal(sanitizeValue(m_dateTimeEditElement->value()), DispatchNoEvent);
    updateClearButtonVisibility();
}
