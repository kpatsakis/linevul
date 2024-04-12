void JSTestObjConstructor::finishCreation(ExecState* exec, JSDOMGlobalObject* globalObject)
{
    Base::finishCreation(exec->globalData());
    ASSERT(inherits(&s_info));
    putDirect(exec->globalData(), exec->propertyNames().prototype, JSTestObjPrototype::self(exec, globalObject), DontDelete | ReadOnly);
    putDirect(exec->globalData(), exec->propertyNames().length, jsNumber(1), ReadOnly | DontDelete | DontEnum);
}
