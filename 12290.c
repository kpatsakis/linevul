void FrameLoaderClient::didChangeTitle(WebCore::DocumentLoader *l)
{
    setTitle(l->title(), l->url());
}
