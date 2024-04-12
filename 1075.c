void JSTestNamedConstructorOwner::finalize(JSC::Handle<JSC::Unknown> handle, void* context)
{
    JSTestNamedConstructor* jsTestNamedConstructor = jsCast<JSTestNamedConstructor*>(handle.get().asCell());
    DOMWrapperWorld* world = static_cast<DOMWrapperWorld*>(context);
    uncacheWrapper(world, jsTestNamedConstructor->impl(), jsTestNamedConstructor);
    jsTestNamedConstructor->releaseImpl();
}
