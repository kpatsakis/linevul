static void VoidMethodEventTargetArgMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestObject* impl = V8TestObject::ToImpl(info.Holder());

  if (UNLIKELY(info.Length() < 1)) {
    V8ThrowException::ThrowTypeError(info.GetIsolate(), ExceptionMessages::FailedToExecute("voidMethodEventTargetArg", "TestObject", ExceptionMessages::NotEnoughArguments(1, info.Length())));
    return;
  }

  EventTarget* event_target_arg;
  event_target_arg = V8EventTarget::ToImplWithTypeCheck(info.GetIsolate(), info[0]);
  if (!event_target_arg) {
    V8ThrowException::ThrowTypeError(info.GetIsolate(), ExceptionMessages::FailedToExecute("voidMethodEventTargetArg", "TestObject", ExceptionMessages::ArgumentNotOfType(0, "EventTarget")));
    return;
  }

  impl->voidMethodEventTargetArg(event_target_arg);
}
