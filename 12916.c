static void VoidMethodDefaultDoubleArgMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  ExceptionState exception_state(info.GetIsolate(), ExceptionState::kExecutionContext, "TestObject", "voidMethodDefaultDoubleArg");

  TestObject* impl = V8TestObject::ToImpl(info.Holder());

  double default_double_arg;
  if (!info[0]->IsUndefined()) {
    default_double_arg = NativeValueTraits<IDLDouble>::NativeValue(info.GetIsolate(), info[0], exception_state);
    if (exception_state.HadException())
      return;
  } else {
    default_double_arg = 0.5;
  }

  impl->voidMethodDefaultDoubleArg(default_double_arg);
}
