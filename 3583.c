void GraphicsContext::drawEllipse(const IntRect& rect)
{
    if (paintingDisabled())
        return;

    m_data->context->SetPen(wxPen(strokeColor(), strokeThickness(), strokeStyleToWxPenStyle(strokeStyle())));
    m_data->context->DrawEllipse(rect.x(), rect.y(), rect.width(), rect.height());
}
