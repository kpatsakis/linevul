 static void AddElementsToKeyAccumulatorImpl(Handle<JSObject> receiver,
 KeyAccumulator* accumulator,
 AddKeyConversion convert) {
 Isolate* isolate = receiver->GetIsolate();
 Handle<String> string(GetString(*receiver), isolate);
    string = String::Flatten(string);
 uint32_t length = static_cast<uint32_t>(string->length());
 for (uint32_t i = 0; i < length; i++) {
      accumulator->AddKey(
          isolate->factory()->LookupSingleCharacterStringFromCode(
              string->Get(i)),
          convert);
 }
 BackingStoreAccessor::AddElementsToKeyAccumulatorImpl(receiver, accumulator,
                                                          convert);
 }
