std::string GLES2Util::GetQualifiedEnumString(const EnumToString* table,
                                              size_t count,
                                              uint32_t value) {
  for (const EnumToString* end = table + count; table < end; ++table) {
    if (table->value == value) {
      return table->name;
    }
  }
  return GetStringEnum(value);
}
