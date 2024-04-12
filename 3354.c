static void VoidMethodSequenceTestInterfaceEmptyArgMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  ExceptionState exception_state(info.GetIsolate(), ExceptionState::kExecutionContext, "TestObject", "voidMethodSequenceTestInterfaceEmptyArg");

  TestObject* impl = V8TestObject::ToImpl(info.Holder());

  if (UNLIKELY(info.Length() < 1)) {
    exception_state.ThrowTypeError(ExceptionMessages::NotEnoughArguments(1, info.Length()));
    return;
  }

  HeapVector<Member<TestInterfaceEmpty>> test_interface_empty_sequence_arg;
  test_interface_empty_sequence_arg = NativeValueTraits<IDLSequence<TestInterfaceEmpty>>::NativeValue(info.GetIsolate(), info[0], exception_state);
  if (exception_state.HadException())
    return;

  impl->voidMethodSequenceTestInterfaceEmptyArg(test_interface_empty_sequence_arg);
}
