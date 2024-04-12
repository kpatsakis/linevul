 static void DeleteImpl(Handle<JSObject> obj, uint32_t entry) {
 Handle<SeededNumberDictionary> dict(
 SeededNumberDictionary::cast(obj->elements()));
 uint32_t index = GetIndexForEntryImpl(*dict, entry);
 Handle<Object> result = SeededNumberDictionary::DeleteProperty(dict, entry);
    USE(result);
    DCHECK(result->IsTrue(dict->GetIsolate()));
 Handle<FixedArray> new_elements =
 SeededNumberDictionary::Shrink(dict, index);
    obj->set_elements(*new_elements);
 }
