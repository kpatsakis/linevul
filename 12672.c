static Maybe<int64_t> IndexOfValueSlowPath(Isolate* isolate,
 Handle<JSObject> receiver,
 Handle<Object> value,
 uint32_t start_from,
 uint32_t length) {
 for (uint32_t k = start_from; k < length; ++k) {
 LookupIterator it(isolate, receiver, k);
 if (!it.IsFound()) {
 continue;
 }
 Handle<Object> element_k;
    ASSIGN_RETURN_ON_EXCEPTION_VALUE(
        isolate, element_k, Object::GetProperty(&it), Nothing<int64_t>());

 if (value->StrictEquals(*element_k)) return Just<int64_t>(k);
 }


   return Just<int64_t>(-1);
 }
