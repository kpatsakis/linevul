 static void ReconfigureImpl(Handle<JSObject> object,
 Handle<FixedArrayBase> store, uint32_t entry,
 Handle<Object> value,
 PropertyAttributes attributes) {
 Handle<SeededNumberDictionary> dictionary =
 JSObject::NormalizeElements(object);
 FixedArray::cast(*store)->set(1, *dictionary);
 uint32_t length = static_cast<uint32_t>(store->length()) - 2;
 if (entry >= length) {
      entry = dictionary->FindEntry(entry - length) + length;
 }
 SlowSloppyArgumentsElementsAccessor::ReconfigureImpl(object, store, entry,
                                                         value, attributes);
 }
