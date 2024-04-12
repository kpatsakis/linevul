static const HashTable* getJSFloat64ArrayPrototypeTable(ExecState* exec)
{
    return getHashTableForGlobalData(exec->globalData(), &JSFloat64ArrayPrototypeTable);
}
