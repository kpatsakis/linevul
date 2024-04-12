InspectorStyleInvalidatorInvalidateEvent::SelectorPart(
    Element& element,
    const char* reason,
    const InvalidationSet& invalidation_set,
    const String& selector_part) {
  std::unique_ptr<TracedValue> value = FillCommonPart(element, reason);
  value->BeginArray("invalidationList");
  invalidation_set.ToTracedValue(value.get());
  value->EndArray();
  value->SetString("selectorPart", selector_part);
  return value;
}
