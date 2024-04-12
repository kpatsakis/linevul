InspectorStyleRecalcInvalidationTrackingEvent::Data(
    Node* node,
    const StyleChangeReasonForTracing& reason) {
  DCHECK(node);

  std::unique_ptr<TracedValue> value = TracedValue::Create();
  value->SetString("frame", ToHexString(node->GetDocument().GetFrame()));
  SetNodeInfo(value.get(), node, "nodeId", "nodeName");
  value->SetString("reason", reason.ReasonString());
  value->SetString("extraData", reason.GetExtraData());
  SourceLocation::Capture()->ToTracedValue(value.get(), "stackTrace");
  return value;
}
