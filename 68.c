EncodedJSValue JSC_HOST_CALL jsTestSerializedScriptValueInterfacePrototypeFunctionMultiTransferList(ExecState* exec)
{
    JSValue thisValue = exec->hostThisValue();
    if (!thisValue.inherits(&JSTestSerializedScriptValueInterface::s_info))
        return throwVMTypeError(exec);
    JSTestSerializedScriptValueInterface* castedThis = jsCast<JSTestSerializedScriptValueInterface*>(asObject(thisValue));
    ASSERT_GC_OBJECT_INHERITS(castedThis, &JSTestSerializedScriptValueInterface::s_info);
    TestSerializedScriptValueInterface* impl = static_cast<TestSerializedScriptValueInterface*>(castedThis->impl());

    size_t argsCount = exec->argumentCount();
    if (argsCount <= 0) {
        impl->multiTransferList();
        return JSValue::encode(jsUndefined());
    }

    RefPtr<SerializedScriptValue> first(SerializedScriptValue::create(exec, MAYBE_MISSING_PARAMETER(exec, 0, DefaultIsUndefined)));
    if (exec->hadException())
        return JSValue::encode(jsUndefined());
    if (argsCount <= 1) {
        impl->multiTransferList(first);
        return JSValue::encode(jsUndefined());
    }

    Array* tx(toArray(MAYBE_MISSING_PARAMETER(exec, 1, DefaultIsUndefined)));
    if (exec->hadException())
        return JSValue::encode(jsUndefined());
    if (argsCount <= 2) {
        impl->multiTransferList(first, tx);
        return JSValue::encode(jsUndefined());
    }

    RefPtr<SerializedScriptValue> second(SerializedScriptValue::create(exec, MAYBE_MISSING_PARAMETER(exec, 2, DefaultIsUndefined)));
    if (exec->hadException())
        return JSValue::encode(jsUndefined());
    if (argsCount <= 3) {
        impl->multiTransferList(first, tx, second);
        return JSValue::encode(jsUndefined());
    }

    Array* txx(toArray(MAYBE_MISSING_PARAMETER(exec, 3, DefaultIsUndefined)));
    if (exec->hadException())
        return JSValue::encode(jsUndefined());
    impl->multiTransferList(first, tx, second, txx);
    return JSValue::encode(jsUndefined());
}
