PassOwnPtr<LifecycleNotifier> Document::createLifecycleNotifier()
{
    return DocumentLifecycleNotifier::create(this);
}
