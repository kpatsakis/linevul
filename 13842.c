PNET_BUFFER_LIST CNBL::DetachInternalObject()
{

    if (IsLSO())
    {
        m_LsoInfo.LsoV1TransmitComplete.TcpPayload = m_TransferSize;
    }

    NET_BUFFER_LIST_INFO(m_NBL, TcpLargeSendNetBufferListInfo) = m_LsoInfo.Value;

    auto Res = m_NBL;
    m_NBL = nullptr;
    return Res;
}
