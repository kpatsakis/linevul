static void VoidMethodLongLongArgMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  ExceptionState exception_state(info.GetIsolate(), ExceptionState::kExecutionContext, "TestObject", "voidMethodLongLongArg");

  TestObject* impl = V8TestObject::ToImpl(info.Holder());

  if (UNLIKELY(info.Length() < 1)) {
    exception_state.ThrowTypeError(ExceptionMessages::NotEnoughArguments(1, info.Length()));
    return;
  }

  int64_t long_long_arg;
  long_long_arg = NativeValueTraits<IDLLongLong>::NativeValue(info.GetIsolate(), info[0], exception_state);
  if (exception_state.HadException())
    return;

  impl->voidMethodLongLongArg(long_long_arg);
}
