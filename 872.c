bool JPEGImageDecoder::setSize(unsigned width, unsigned height)
{
    if (!ImageDecoder::setSize(width, height))
        return false;

    prepareScaleDataIfNecessary();
    return true;
}
