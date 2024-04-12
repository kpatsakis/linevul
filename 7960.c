void InspectorOverlay::drawViewSize()
{
    if (m_drawViewSize)
         evaluateInOverlay("drawViewSize", m_drawViewSizeWithGrid ? "true" : "false");
 }
