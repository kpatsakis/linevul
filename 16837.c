void DocumentLoader::setMainDocumentError(const ResourceError& error)
{
    m_mainDocumentError = error;    
    frameLoader()->client()->setMainDocumentError(this, error);
}
