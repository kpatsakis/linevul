v8::Local<v8::Value> SerializedScriptValue::deserialize(MessagePortArray* messagePorts)
{
    return deserialize(v8::Isolate::GetCurrent(), messagePorts, 0);
}
