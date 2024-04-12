void InputMethodIBus::ExtractCompositionText(
    const chromeos::IBusText& text,
    uint32 cursor_position,
    CompositionText* out_composition) const {
  out_composition->Clear();
  out_composition->text = UTF8ToUTF16(text.text());

  if (out_composition->text.empty())
    return;

  std::vector<size_t> char16_offsets;
  size_t length = out_composition->text.length();
  base::i18n::UTF16CharIterator char_iterator(&out_composition->text);
  do {
    char16_offsets.push_back(char_iterator.array_pos());
  } while (char_iterator.Advance());

  uint32 char_length = static_cast<uint32>(char16_offsets.size());
  char16_offsets.push_back(length);

  size_t cursor_offset =
      char16_offsets[std::min(char_length, cursor_position)];

  out_composition->selection = gfx::Range(cursor_offset);

  const std::vector<chromeos::IBusText::UnderlineAttribute>&
      underline_attributes = text.underline_attributes();
  const std::vector<chromeos::IBusText::SelectionAttribute>&
      selection_attributes = text.selection_attributes();

  if (!underline_attributes.empty()) {
    for (size_t i = 0; i < underline_attributes.size(); ++i) {
      const uint32 start = underline_attributes[i].start_index;
      const uint32 end = underline_attributes[i].end_index;
      if (start >= end)
        continue;
      CompositionUnderline underline(
          char16_offsets[start], char16_offsets[end],
          SK_ColorBLACK, false /* thick */);
      if (underline_attributes[i].type ==
          chromeos::IBusText::IBUS_TEXT_UNDERLINE_DOUBLE)
        underline.thick = true;
      else if (underline_attributes[i].type ==
               chromeos::IBusText::IBUS_TEXT_UNDERLINE_ERROR)
        underline.color = SK_ColorRED;
      out_composition->underlines.push_back(underline);
    }
  }

  if (!selection_attributes.empty()) {
    LOG_IF(ERROR, selection_attributes.size() != 1)
        << "Chrome does not support multiple selection";
    for (uint32 i = 0; i < selection_attributes.size(); ++i) {
      const uint32 start = selection_attributes[i].start_index;
      const uint32 end = selection_attributes[i].end_index;
      if (start >= end)
        continue;
      CompositionUnderline underline(
          char16_offsets[start], char16_offsets[end],
          SK_ColorBLACK, true /* thick */);
      out_composition->underlines.push_back(underline);
      if (underline.start_offset == cursor_offset) {
        out_composition->selection.set_start(underline.end_offset);
        out_composition->selection.set_end(cursor_offset);
      } else if (underline.end_offset == cursor_offset) {
        out_composition->selection.set_start(underline.start_offset);
        out_composition->selection.set_end(cursor_offset);
      }
    }
  }

  if (out_composition->underlines.empty()) {
    out_composition->underlines.push_back(CompositionUnderline(
        0, length, SK_ColorBLACK, false /* thick */));
   }
 }
