static Mutex& threadSetMutex()
{
    AtomicallyInitializedStaticReference(Mutex, mutex, new Mutex);
    return mutex;
}
