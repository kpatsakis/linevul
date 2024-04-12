void GraphicsContext::clip(const FloatRect& r)
{
    m_data->context->SetClippingRegion(r.x(), r.y(), r.width(), r.height());
}
