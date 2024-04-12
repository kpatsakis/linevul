void setJSTestObjWithScriptExecutionContextAttribute(ExecState* exec, JSObject* thisObject, JSValue value)
{
    JSTestObj* castedThis = jsCast<JSTestObj*>(thisObject);
    TestObj* impl = static_cast<TestObj*>(castedThis->impl());
    ScriptExecutionContext* scriptContext = jsCast<JSDOMGlobalObject*>(exec->lexicalGlobalObject())->scriptExecutionContext();
    if (!scriptContext)
        return;
    impl->setWithScriptExecutionContextAttribute(scriptContext, toTestObj(value));
}
