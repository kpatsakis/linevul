void Document::enqueueHashchangeEvent(const String& oldURL, const String& newURL)
{
    enqueueWindowEvent(HashChangeEvent::create(oldURL, newURL));
}
