bool JSTestInterfaceOwner::isReachableFromOpaqueRoots(JSC::Handle<JSC::Unknown> handle, void*, SlotVisitor& visitor)
{
    JSTestInterface* jsTestInterface = jsCast<JSTestInterface*>(handle.get().asCell());
    if (jsTestInterface->impl()->hasPendingActivity())
        return true;
    if (!isObservable(jsTestInterface))
        return false;
    UNUSED_PARAM(visitor);
    return false;
}
