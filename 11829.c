static void optionsObjectMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    if (UNLIKELY(info.Length() < 1)) {
        throwTypeError(ExceptionMessages::failedToExecute("optionsObject", "TestObject", ExceptionMessages::notEnoughArguments(1, info.Length())), info.GetIsolate());
        return;
    }
    TestObject* imp = V8TestObject::toNative(info.Holder());
    V8TRYCATCH_VOID(Dictionary, oo, Dictionary(info[0], info.GetIsolate()));
    if (!oo.isUndefinedOrNull() && !oo.isObject()) {
        throwTypeError(ExceptionMessages::failedToExecute("optionsObject", "TestObject", "parameter 1 ('oo') is not an object."), info.GetIsolate());
        return;
    }
    V8TRYCATCH_VOID(Dictionary, ooo, Dictionary(info[1], info.GetIsolate()));
    if (!ooo.isUndefinedOrNull() && !ooo.isObject()) {
        throwTypeError(ExceptionMessages::failedToExecute("optionsObject", "TestObject", "parameter 2 ('ooo') is not an object."), info.GetIsolate());
        return;
    }
    imp->optionsObject(oo, ooo);
}
