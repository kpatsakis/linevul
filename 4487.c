int Textfield::OnDragUpdated(const ui::DropTargetEvent& event) {
  DCHECK(CanDrop(event.data()));
  gfx::RenderText* render_text = GetRenderText();
  const gfx::Range& selection = render_text->selection();
  drop_cursor_position_ = render_text->FindCursorPosition(event.location());
  bool in_selection =
      !selection.is_empty() &&
      selection.Contains(gfx::Range(drop_cursor_position_.caret_pos()));
  drop_cursor_visible_ = !in_selection;
  OnCaretBoundsChanged();
  SchedulePaint();

  StopBlinkingCursor();

  if (initiating_drag_) {
    if (in_selection)
      return ui::DragDropTypes::DRAG_NONE;
    return event.IsControlDown() ? ui::DragDropTypes::DRAG_COPY
                                 : ui::DragDropTypes::DRAG_MOVE;
  }
  return ui::DragDropTypes::DRAG_COPY | ui::DragDropTypes::DRAG_MOVE;
}
