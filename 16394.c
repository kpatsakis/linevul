 static MaybeHandle<FixedArray> PrependElementIndicesImpl(
 Handle<JSObject> object, Handle<FixedArrayBase> backing_store,
 Handle<FixedArray> keys, GetKeysConversion convert,
 PropertyFilter filter) {
 Isolate* isolate = object->GetIsolate();
 uint32_t nof_property_keys = keys->length();
 uint32_t initial_list_length =
 Subclass::GetMaxNumberOfEntries(*object, *backing_store);

    initial_list_length += nof_property_keys;
 if (initial_list_length > FixedArray::kMaxLength ||
        initial_list_length < nof_property_keys) {
 return isolate->Throw<FixedArray>(isolate->factory()->NewRangeError(
 MessageTemplate::kInvalidArrayLength));
 }

 MaybeHandle<FixedArray> raw_array =
        isolate->factory()->TryNewFixedArray(initial_list_length);
 Handle<FixedArray> combined_keys;

 if (!raw_array.ToHandle(&combined_keys)) {
 if (IsHoleyElementsKind(kind())) {
        initial_list_length =
 Subclass::NumberOfElementsImpl(*object, *backing_store);
        initial_list_length += nof_property_keys;
 }
      combined_keys = isolate->factory()->NewFixedArray(initial_list_length);
 }

 uint32_t nof_indices = 0;
 bool needs_sorting =
 IsDictionaryElementsKind(kind()) || IsSloppyArgumentsElements(kind());
    combined_keys = Subclass::DirectCollectElementIndicesImpl(
        isolate, object, backing_store,
        needs_sorting ? GetKeysConversion::kKeepNumbers : convert, filter,
        combined_keys, &nof_indices);

 if (needs_sorting) {
 SortIndices(combined_keys, nof_indices);
 if (convert == GetKeysConversion::kConvertToString) {
 for (uint32_t i = 0; i < nof_indices; i++) {
 Handle<Object> index_string = isolate->factory()->Uint32ToString(
              combined_keys->get(i)->Number());
          combined_keys->set(i, *index_string);
 }
 }
 }

 CopyObjectToObjectElements(*keys, FAST_ELEMENTS, 0, *combined_keys,
                               FAST_ELEMENTS, nof_indices, nof_property_keys);

 if (IsHoleyElementsKind(kind()) || IsSloppyArgumentsElements(kind())) {
 int final_size = nof_indices + nof_property_keys;
      DCHECK_LE(final_size, combined_keys->length());
      combined_keys->Shrink(final_size);
 }

 return combined_keys;
 }
