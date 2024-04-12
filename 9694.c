bool Textfield::GetWordLookupDataFromSelection(
    gfx::DecoratedText* decorated_text,
    gfx::Point* baseline_point) {
  return GetRenderText()->GetLookupDataForRange(GetRenderText()->selection(),
                                                decorated_text, baseline_point);
}
