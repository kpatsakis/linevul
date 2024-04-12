void setJSTestObjWithScriptExecutionContextAndScriptStateAttribute(ExecState* exec, JSObject* thisObject, JSValue value)
{
    JSTestObj* castedThis = jsCast<JSTestObj*>(thisObject);
    TestObj* impl = static_cast<TestObj*>(castedThis->impl());
    ScriptExecutionContext* scriptContext = jsCast<JSDOMGlobalObject*>(exec->lexicalGlobalObject())->scriptExecutionContext();
    if (!scriptContext)
        return;
    impl->setWithScriptExecutionContextAndScriptStateAttribute(exec, scriptContext, toTestObj(value));
}
