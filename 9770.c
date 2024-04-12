 static uint32_t GetMaxNumberOfEntries(JSObject* receiver,
 FixedArrayBase* elements) {
 return Subclass::GetMaxIndex(receiver, elements);
 }
