void AXTableCell::columnIndexRange(std::pair<unsigned, unsigned>& columnRange) {
  if (!m_layoutObject || !m_layoutObject->isTableCell())
    return;

  LayoutTableCell* cell = toLayoutTableCell(m_layoutObject);
  columnRange.first = cell->table()->absoluteColumnToEffectiveColumn(
      cell->absoluteColumnIndex());
  columnRange.second = cell->table()->absoluteColumnToEffectiveColumn(
                           cell->absoluteColumnIndex() + cell->colSpan()) -
                       columnRange.first;
}
