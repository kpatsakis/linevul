bool Textfield::GetTextRange(gfx::Range* range) const {
  if (!ImeEditingAllowed())
    return false;

  model_->GetTextRange(range);
  return true;
}
