void GraphicsContext::setPlatformCompositeOperation(CompositeOperator op)
{
    if (m_data->context)
    {
#if wxCHECK_VERSION(2,9,0)
        m_data->context->SetLogicalFunction(static_cast<wxRasterOperationMode>(getWxCompositingOperation(op, false)));
#else
        m_data->context->SetLogicalFunction(getWxCompositingOperation(op, false));
#endif
    }
}
