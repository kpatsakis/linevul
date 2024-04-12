PassRefPtr<SerializedScriptValue> SerializedScriptValue::createFromWire(const String& data)
{
    return adoptRef(new SerializedScriptValue(data));
}
