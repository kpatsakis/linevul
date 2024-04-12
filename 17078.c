void setJSTestObjWithScriptExecutionContextAttributeRaises(ExecState* exec, JSObject* thisObject, JSValue value)
{
    JSTestObj* castedThis = jsCast<JSTestObj*>(thisObject);
    TestObj* impl = static_cast<TestObj*>(castedThis->impl());
    ExceptionCode ec = 0;
    ScriptExecutionContext* scriptContext = jsCast<JSDOMGlobalObject*>(exec->lexicalGlobalObject())->scriptExecutionContext();
    if (!scriptContext)
        return;
    impl->setWithScriptExecutionContextAttributeRaises(scriptContext, toTestObj(value), ec);
    setDOMException(exec, ec);
}
