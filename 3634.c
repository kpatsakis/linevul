void LayerWebKitThread::setIsMask(bool isMask)
{
    m_isMask = isMask;
    if (isMask && m_tiler)
        m_tiler->setNeedsBacking(true);
}
