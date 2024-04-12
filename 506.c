bool JPEGImageDecoder::setFailed()
{
    m_reader.clear();
    return ImageDecoder::setFailed();
}
