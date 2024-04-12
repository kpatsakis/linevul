 static void DeleteImpl(Handle<JSObject> holder, uint32_t entry) {
 uint32_t length = static_cast<uint32_t>(GetString(*holder)->length());
 if (entry < length) {
 return; // String contents can't be deleted.
 }
 BackingStoreAccessor::DeleteImpl(holder, entry - length);
 }
