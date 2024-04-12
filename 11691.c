ReadableStreamBytesConsumer::ReadableStreamBytesConsumer(
    ScriptState* script_state,
    ScriptValue stream_reader)
    : reader_(script_state->GetIsolate(), stream_reader.V8Value()),
      script_state_(script_state) {
  reader_.SetPhantom();
}
