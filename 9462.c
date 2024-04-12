bool JSTestCustomNamedGetterPrototype::getOwnPropertyDescriptor(JSObject* object, ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    JSTestCustomNamedGetterPrototype* thisObject = jsCast<JSTestCustomNamedGetterPrototype*>(object);
    return getStaticFunctionDescriptor<JSObject>(exec, &JSTestCustomNamedGetterPrototypeTable, thisObject, propertyName, descriptor);
}
