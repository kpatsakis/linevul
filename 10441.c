void InspectorPageAgent::didRecalculateStyle()
{
    if (m_enabled)
        m_overlay->update();
}
