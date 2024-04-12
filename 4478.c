static void VoidMethodDoubleOrDOMStringOrNullArgMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  ExceptionState exception_state(info.GetIsolate(), ExceptionState::kExecutionContext, "TestObject", "voidMethodDoubleOrDOMStringOrNullArg");

  TestObject* impl = V8TestObject::ToImpl(info.Holder());

  if (UNLIKELY(info.Length() < 1)) {
    exception_state.ThrowTypeError(ExceptionMessages::NotEnoughArguments(1, info.Length()));
    return;
  }

  DoubleOrString arg;
  V8DoubleOrString::ToImpl(info.GetIsolate(), info[0], arg, UnionTypeConversionMode::kNullable, exception_state);
  if (exception_state.HadException())
    return;

  impl->voidMethodDoubleOrDOMStringOrNullArg(arg);
}
