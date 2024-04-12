void setJSTestObjWithScriptStateAttribute(ExecState* exec, JSObject* thisObject, JSValue value)
{
    JSTestObj* castedThis = jsCast<JSTestObj*>(thisObject);
    TestObj* impl = static_cast<TestObj*>(castedThis->impl());
    impl->setWithScriptStateAttribute(exec, value.toInt32(exec));
}
