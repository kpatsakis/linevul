bool OSExchangeDataProviderAuraX11::GetString(base::string16* result) const {
  if (HasFile()) {
    return false;
  }

  std::vector< ::Atom> text_atoms = ui::GetTextAtomsFrom(&atom_cache_);
  std::vector< ::Atom> requested_types;
  ui::GetAtomIntersection(text_atoms, GetTargets(), &requested_types);

  ui::SelectionData data(format_map_.GetFirstOf(requested_types));
  if (data.IsValid()) {
    std::string text = data.GetText();
    *result = base::UTF8ToUTF16(text);
    return true;
  }

  return false;
 }
