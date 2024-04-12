void setJSTestObjLongSequenceAttr(ExecState* exec, JSObject* thisObject, JSValue value)
{
    JSTestObj* castedThis = jsCast<JSTestObj*>(thisObject);
    TestObj* impl = static_cast<TestObj*>(castedThis->impl());
    impl->setLongSequenceAttr(toNativeArray<long>(exec, value));
}
