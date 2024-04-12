bool NPJSObject::invoke(ExecState* exec, JSGlobalObject* globalObject, JSValue function, const NPVariant* arguments, uint32_t argumentCount, NPVariant* result)
{
    CallData callData;
    CallType callType = getCallData(function, callData);
    if (callType == CallTypeNone)
        return false;

    MarkedArgumentBuffer argumentList;
    for (uint32_t i = 0; i < argumentCount; ++i)
        argumentList.append(m_objectMap->convertNPVariantToJSValue(exec, globalObject, arguments[i]));

    exec->globalData().timeoutChecker.start();
    JSValue value = JSC::call(exec, function, callType, callData, m_jsObject, argumentList);
    exec->globalData().timeoutChecker.stop();

    m_objectMap->convertJSValueToNPVariant(exec, value, *result);
    exec->clearException();
    
    return true;
}
