StaticRangeVector* RangesFromCurrentSelectionOrExtendCaret(
    const LocalFrame& frame,
    SelectionModifyDirection direction,
    TextGranularity granularity) {
  frame.GetDocument()->UpdateStyleAndLayoutIgnorePendingStylesheets();
  SelectionModifier selection_modifier(
      frame, frame.Selection().ComputeVisibleSelectionInDOMTreeDeprecated());
  if (selection_modifier.Selection().IsCaret())
    selection_modifier.Modify(SelectionModifyAlteration::kExtend, direction,
                              granularity);
  StaticRangeVector* ranges = new StaticRangeVector;
  if (selection_modifier.Selection().IsNone())
    return ranges;
  ranges->push_back(StaticRange::Create(
      FirstEphemeralRangeOf(selection_modifier.Selection())));
  return ranges;
}
