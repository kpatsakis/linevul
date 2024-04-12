std::unique_ptr<TracedValue> InspectorLayerInvalidationTrackingEvent::Data(
    const PaintLayer* layer,
    const char* reason) {
  const LayoutObject& paint_invalidation_container =
      layer->GetLayoutObject().ContainerForPaintInvalidation();

  std::unique_ptr<TracedValue> value = TracedValue::Create();
  value->SetString("frame",
                   ToHexString(paint_invalidation_container.GetFrame()));
  SetGeneratingNodeInfo(value.get(), &paint_invalidation_container, "paintId");
  value->SetString("reason", reason);
  return value;
}
