String Editor::SelectionStartCSSPropertyValue(CSSPropertyID property_id) {
  EditingStyle* selection_style =
      EditingStyleUtilities::CreateStyleAtSelectionStart(
          GetFrame().Selection().ComputeVisibleSelectionInDOMTreeDeprecated(),
          property_id == CSSPropertyBackgroundColor);
  if (!selection_style || !selection_style->Style())
    return String();

  if (property_id == CSSPropertyFontSize)
    return String::Number(
        selection_style->LegacyFontSize(GetFrame().GetDocument()));
  return selection_style->Style()->GetPropertyValue(property_id);
}
