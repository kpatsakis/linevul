  virtual string16 Execute(
      const std::string& component_text,
      std::vector<size_t>* offsets_into_component) const {
    return IDNToUnicodeWithOffsets(component_text, languages_,
                                   offsets_into_component);
  }
