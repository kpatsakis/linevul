bool GIFImageReader::parse(GIFImageDecoder::GIFParseQuery query)
{
    ASSERT(m_bytesRead <= m_data->size());

    return parseData(m_bytesRead, m_data->size() - m_bytesRead, query);
}
