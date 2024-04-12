JSValue jsTestObjWithScriptExecutionContextAndScriptStateWithSpacesAttribute(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSTestObj* castedThis = jsCast<JSTestObj*>(asObject(slotBase));
    ScriptExecutionContext* scriptContext = jsCast<JSDOMGlobalObject*>(exec->lexicalGlobalObject())->scriptExecutionContext();
    if (!scriptContext)
        return jsUndefined();
    TestObj* impl = static_cast<TestObj*>(castedThis->impl());
    JSValue result = toJS(exec, castedThis->globalObject(), WTF::getPtr(impl->withScriptExecutionContextAndScriptStateWithSpacesAttribute(exec, scriptContext)));
    return result;
}
