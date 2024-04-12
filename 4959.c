JSValue jsTestObjUnsignedLongSequenceAttr(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSTestObj* castedThis = jsCast<JSTestObj*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    TestObj* impl = static_cast<TestObj*>(castedThis->impl());
    JSValue result = jsArray(exec, castedThis->globalObject(), impl->unsignedLongSequenceAttr());
    return result;
}
