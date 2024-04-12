PassRefPtr<SerializedScriptValue> SerializedScriptValue::nullValue()
{
    SerializedScriptValueWriter writer;
    writer.writeNull();
    String wireData = writer.takeWireString();
    return adoptRef(new SerializedScriptValue(wireData));
}
