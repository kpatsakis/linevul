static void GetMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  ExceptionState exception_state(info.GetIsolate(), ExceptionState::kExecutionContext, "TestObject", "get");

  TestObject* impl = V8TestObject::ToImpl(info.Holder());

  ScriptState* script_state = ScriptState::ForRelevantRealm(info);

  if (UNLIKELY(info.Length() < 1)) {
    exception_state.ThrowTypeError(ExceptionMessages::NotEnoughArguments(1, info.Length()));
    return;
  }

  int32_t key;
  key = NativeValueTraits<IDLLongEnforceRange>::NativeValue(info.GetIsolate(), info[0], exception_state);
  if (exception_state.HadException())
    return;

  ScriptValue result = impl->getForBinding(script_state, key, exception_state);
  if (exception_state.HadException()) {
    return;
  }
  V8SetReturnValue(info, result.V8Value());
}
