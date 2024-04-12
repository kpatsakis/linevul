void FrameSelection::DidSetSelectionDeprecated(
    const SetSelectionData& options) {
  const Document& current_document = GetDocument();
  if (!GetSelectionInDOMTree().IsNone() && !options.DoNotSetFocus()) {
    SetFocusedNodeIfNeeded();
    if (!IsAvailable() || GetDocument() != current_document) {
      NOTREACHED();
      return;
    }
  }

  frame_caret_->StopCaretBlinkTimer();
  UpdateAppearance();

  x_pos_for_vertical_arrow_navigation_ = NoXPosForVerticalArrowNavigation();

  if (!options.DoNotSetFocus()) {
    SelectFrameElementInParentIfFullySelected();
    if (!IsAvailable() || GetDocument() != current_document) {
      return;
    }
  }
  const SetSelectionBy set_selection_by = options.GetSetSelectionBy();
  NotifyTextControlOfSelectionChange(set_selection_by);
  if (set_selection_by == SetSelectionBy::kUser) {
    const CursorAlignOnScroll align = options.GetCursorAlignOnScroll();
    ScrollAlignment alignment;

    if (frame_->GetEditor()
            .Behavior()
            .ShouldCenterAlignWhenSelectionIsRevealed())
      alignment = (align == CursorAlignOnScroll::kAlways)
                      ? ScrollAlignment::kAlignCenterAlways
                      : ScrollAlignment::kAlignCenterIfNeeded;
    else
      alignment = (align == CursorAlignOnScroll::kAlways)
                      ? ScrollAlignment::kAlignTopAlways
                      : ScrollAlignment::kAlignToEdgeIfNeeded;

    RevealSelection(alignment, kRevealExtent);
  }

  NotifyAccessibilityForSelectionChange();
  NotifyCompositorForSelectionChange();
  NotifyEventHandlerForSelectionChange();
  frame_->DomWindow()->EnqueueDocumentEvent(
      Event::Create(EventTypeNames::selectionchange));
}
