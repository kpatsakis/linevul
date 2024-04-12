void GraphicsContext::setPlatformFillColor(const Color& color, ColorSpace colorSpace)
{
    if (paintingDisabled())
        return;
    
    if (m_data->context)
        m_data->context->SetBrush(wxBrush(color));
}
