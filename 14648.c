  static v8::Local<v8::Function> CreateFunction(
      ScriptState* script_state,
      ReadableStreamBytesConsumer* consumer) {
    return (new OnFulfilled(script_state, consumer))->BindToV8Function();
  }
