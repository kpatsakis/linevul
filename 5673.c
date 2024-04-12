DEFINE_TRACE(ServiceWorkerContainer)
{
    visitor->trace(m_controller);
    visitor->trace(m_ready);
    RefCountedGarbageCollectedEventTargetWithInlineData<ServiceWorkerContainer>::trace(visitor);
    ContextLifecycleObserver::trace(visitor);
}
