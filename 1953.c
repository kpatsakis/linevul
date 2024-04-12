void V8TestObj::derefObject(void* object)
{
    static_cast<TestObj*>(object)->deref();
}
