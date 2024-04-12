JSObject* JSTestSerializedScriptValueInterface::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return JSTestSerializedScriptValueInterfacePrototype::create(exec->globalData(), globalObject, JSTestSerializedScriptValueInterfacePrototype::createStructure(globalObject->globalData(), globalObject, globalObject->objectPrototype()));
}
