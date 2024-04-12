 static Handle<Object> GetInternalImpl(Handle<JSObject> holder,
 uint32_t entry) {
 return Subclass::GetImpl(holder->GetIsolate(), holder->elements(), entry);
 }
