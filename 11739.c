void Label::SetAllowCharacterBreak(bool allow_character_break) {
  if (allow_character_break != allow_character_break_) {
    allow_character_break_ = allow_character_break;
    text_size_valid_ = false;
    PreferredSizeChanged();
    SchedulePaint();
  }
}
