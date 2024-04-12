JSTestObj::JSTestObj(Structure* structure, JSDOMGlobalObject* globalObject, PassRefPtr<TestObj> impl)
    : JSDOMWrapper(structure, globalObject)
    , m_impl(impl.leakRef())
{
}
