void HTMLInputElement::setCanReceiveDroppedFiles(bool canReceiveDroppedFiles)
{
    if (m_canReceiveDroppedFiles == canReceiveDroppedFiles)
        return;
    m_canReceiveDroppedFiles = canReceiveDroppedFiles;
    if (renderer())
        renderer()->updateFromElement();
}
