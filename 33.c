void GraphicsContext::scale(const FloatSize& scale) 
{ 
#if USE(WXGC)
    if (m_data->context) {
        wxGraphicsContext* gc = m_data->context->GetGraphicsContext();
        gc->Scale(scale.width(), scale.height());
    }
#endif
}
