int ConvertFromWeb(blink::WebDragOperationsMask ops) {
  int drag_op = ui::DragDropTypes::DRAG_NONE;
  if (ops & blink::WebDragOperationCopy)
    drag_op |= ui::DragDropTypes::DRAG_COPY;
  if (ops & blink::WebDragOperationMove)
    drag_op |= ui::DragDropTypes::DRAG_MOVE;
  if (ops & blink::WebDragOperationLink)
    drag_op |= ui::DragDropTypes::DRAG_LINK;
  return drag_op;
}
