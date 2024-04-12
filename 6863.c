void ImageBitmapFactories::addLoader(PassRefPtr<ImageBitmapLoader> loader)
{
    m_pendingLoaders.add(loader);
}
