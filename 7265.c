bool JSTestEventTargetConstructor::getOwnPropertyDescriptor(JSObject* object, ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSTestEventTargetConstructor, JSDOMWrapper>(exec, &JSTestEventTargetConstructorTable, jsCast<JSTestEventTargetConstructor*>(object), propertyName, descriptor);
}
