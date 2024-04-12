void JSTestNamedConstructorNamedConstructor::finishCreation(ExecState* exec, JSDOMGlobalObject* globalObject)
{
    Base::finishCreation(globalObject);
    ASSERT(inherits(&s_info));
    putDirect(exec->globalData(), exec->propertyNames().prototype, JSTestNamedConstructorPrototype::self(exec, globalObject), None);
}
