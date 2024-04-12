bool JSTestInterfaceConstructor::getOwnPropertySlot(JSCell* cell, ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticPropertySlot<JSTestInterfaceConstructor, JSDOMWrapper>(exec, &JSTestInterfaceConstructorTable, jsCast<JSTestInterfaceConstructor*>(cell), propertyName, slot);
}
