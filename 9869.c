void BlockPainter::PaintAllChildPhasesAtomically(
    const LayoutBox& child,
    const PaintInfo& paint_info,
    const LayoutPoint& paint_offset) {
  LayoutPoint child_point =
      layout_block_.FlipForWritingModeForChildForPaint(&child, paint_offset);
  if (!child.HasSelfPaintingLayer() && !child.IsFloating())
    ObjectPainter(child).PaintAllPhasesAtomically(paint_info, child_point);
}
