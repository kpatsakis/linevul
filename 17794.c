static bool isHostObject(v8::Handle<v8::Object> object)
{
    return object->InternalFieldCount() || object->HasIndexedPropertiesInExternalArrayData();
}
