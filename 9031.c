String Document::encoding() const
{
    if (TextResourceDecoder* d = decoder())
        return d->encoding().domName();
    return String();
}
