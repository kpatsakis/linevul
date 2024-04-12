 static void TransitionElementsKindImpl(Handle<JSObject> object,
 Handle<Map> to_map) {
 Handle<Map> from_map = handle(object->map());
 ElementsKind from_kind = from_map->elements_kind();
 ElementsKind to_kind = to_map->elements_kind();
 if (IsFastHoleyElementsKind(from_kind)) {
      to_kind = GetHoleyElementsKind(to_kind);
 }
 if (from_kind != to_kind) {
      DCHECK(IsFastElementsKind(from_kind));
      DCHECK(IsFastElementsKind(to_kind));
      DCHECK_NE(TERMINAL_FAST_ELEMENTS_KIND, from_kind);

 Handle<FixedArrayBase> from_elements(object->elements());
 if (object->elements() == object->GetHeap()->empty_fixed_array() ||
 IsFastDoubleElementsKind(from_kind) ==
 IsFastDoubleElementsKind(to_kind)) {
 JSObject::MigrateToMap(object, to_map);
 } else {
        DCHECK((IsFastSmiElementsKind(from_kind) &&
 IsFastDoubleElementsKind(to_kind)) ||
 (IsFastDoubleElementsKind(from_kind) &&
 IsFastObjectElementsKind(to_kind)));
 uint32_t capacity = static_cast<uint32_t>(object->elements()->length());
 Handle<FixedArrayBase> elements = ConvertElementsWithCapacity(
            object, from_elements, from_kind, capacity);
 JSObject::SetMapAndElements(object, to_map, elements);
 }
 if (FLAG_trace_elements_transitions) {
 JSObject::PrintElementsTransition(stdout, object, from_kind,
                                          from_elements, to_kind,
                                          handle(object->elements()));
 }
 }
 }
