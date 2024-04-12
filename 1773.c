void BaseMultipleFieldsDateAndTimeInputType::readonlyAttributeChanged()
{
    m_spinButtonElement->releaseCapture();
    m_clearButton->releaseCapture();
    if (m_dateTimeEditElement)
        m_dateTimeEditElement->readOnlyStateChanged();
}
