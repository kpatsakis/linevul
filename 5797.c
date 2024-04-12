static void VoidMethodDefaultUndefinedLongArgMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  ExceptionState exception_state(info.GetIsolate(), ExceptionState::kExecutionContext, "TestObject", "voidMethodDefaultUndefinedLongArg");

  TestObject* impl = V8TestObject::ToImpl(info.Holder());

  int32_t default_undefined_long_arg;
  default_undefined_long_arg = NativeValueTraits<IDLLong>::NativeValue(info.GetIsolate(), info[0], exception_state);
  if (exception_state.HadException())
    return;

  impl->voidMethodDefaultUndefinedLongArg(default_undefined_long_arg);
}
