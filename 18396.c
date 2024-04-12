 static Handle<JSArray> SpliceImpl(Handle<JSArray> receiver,
 uint32_t start, uint32_t delete_count,
 Arguments* args, uint32_t add_count) {
 Isolate* isolate = receiver->GetIsolate();
 Heap* heap = isolate->heap();
 uint32_t length = Smi::cast(receiver->length())->value();
 uint32_t new_length = length - delete_count + add_count;

 ElementsKind kind = KindTraits::Kind;
 if (new_length <= static_cast<uint32_t>(receiver->elements()->length()) &&
 IsFastSmiOrObjectElementsKind(kind)) {
 HandleScope scope(isolate);
 JSObject::EnsureWritableFastElements(receiver);
 }

 Handle<FixedArrayBase> backing_store(receiver->elements(), isolate);

 if (new_length == 0) {
      receiver->set_elements(heap->empty_fixed_array());
      receiver->set_length(Smi::kZero);
 return isolate->factory()->NewJSArrayWithElements(
          backing_store, KindTraits::Kind, delete_count);
 }

 Handle<JSArray> deleted_elements = isolate->factory()->NewJSArray(
 KindTraits::Kind, delete_count, delete_count);
 if (delete_count > 0) {
 DisallowHeapAllocation no_gc;
 Subclass::CopyElementsImpl(*backing_store, start,
                                 deleted_elements->elements(), KindTraits::Kind,
 0, kPackedSizeNotKnown, delete_count);
 }

 if (add_count < delete_count) {
 Subclass::SpliceShrinkStep(isolate, receiver, backing_store, start,
                                 delete_count, add_count, length, new_length);
 } else if (add_count > delete_count) {
      backing_store =
 Subclass::SpliceGrowStep(isolate, receiver, backing_store, start,
                                   delete_count, add_count, length, new_length);
 }

 Subclass::CopyArguments(args, backing_store, add_count, 3, start);

    receiver->set_length(Smi::FromInt(new_length));
 Subclass::TryTransitionResultArrayToPacked(deleted_elements);
 return deleted_elements;
 }
