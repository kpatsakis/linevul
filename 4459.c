bool Editor::deleteSelectionAfterDraggingWithEvents(
    Element* dragSource,
    DeleteMode deleteMode,
    const Position& referenceMovePosition) {
  if (!dragSource || !dragSource->isConnected())
    return true;

  const bool shouldDelete = dispatchBeforeInputEditorCommand(
                                dragSource, InputEvent::InputType::DeleteByDrag,
                                targetRangesForInputEvent(*dragSource)) ==
                            DispatchEventResult::NotCanceled;

  if (m_frame->document()->frame() != m_frame)
    return false;

  if (shouldDelete && dragSource->isConnected()) {
    deleteSelectionWithSmartDelete(
        deleteMode, InputEvent::InputType::DeleteByDrag, referenceMovePosition);
  }

  return true;
}
