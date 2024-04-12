 static Handle<FixedArrayBase> ConvertElementsWithCapacity(
 Handle<JSObject> object, Handle<FixedArrayBase> old_elements,
 ElementsKind from_kind, uint32_t capacity, int copy_size) {
 return ConvertElementsWithCapacity(object, old_elements, from_kind,
                                       capacity, 0, 0, copy_size);
 }
