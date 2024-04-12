bool JPEGImageDecoder::outputScanlines(ImageFrame& buffer)
{
    return m_scaled ? outputScanlines<colorSpace, true>(buffer) : outputScanlines<colorSpace, false>(buffer);
}
