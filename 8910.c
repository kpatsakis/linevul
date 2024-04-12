 static bool HasEntryImpl(Isolate* isolate, FixedArrayBase* store,
 uint32_t entry) {
 DisallowHeapAllocation no_gc;
 SeededNumberDictionary* dict = SeededNumberDictionary::cast(store);
 Object* index = dict->KeyAt(entry);
 return !index->IsTheHole(isolate);
 }
