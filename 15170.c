 static bool HasEntryImpl(Isolate* isolate, FixedArrayBase* backing_store,
 uint32_t entry) {
 return !BackingStore::cast(backing_store)->is_the_hole(isolate, entry);
 }
