 static uint32_t GetEntryForIndexImpl(Isolate* isolate, JSObject* holder,
 FixedArrayBase* store, uint32_t index,
 PropertyFilter filter) {
 DisallowHeapAllocation no_gc;
 SeededNumberDictionary* dictionary = SeededNumberDictionary::cast(store);
 int entry = dictionary->FindEntry(isolate, index);
 if (entry == SeededNumberDictionary::kNotFound) return kMaxUInt32;
 if (filter != ALL_PROPERTIES) {
 PropertyDetails details = dictionary->DetailsAt(entry);
 PropertyAttributes attr = details.attributes();
 if ((attr & filter) != 0) return kMaxUInt32;
 }
 return static_cast<uint32_t>(entry);
 }
