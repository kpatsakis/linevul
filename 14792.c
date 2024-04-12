void AppendColumnList(std::string* output) {
  const char* joiner = " ";
  for (int i = BEGIN_FIELDS; i < BEGIN_FIELDS + FIELD_COUNT; ++i) {
    output->append(joiner);
    output->append(ColumnName(i));
    joiner = ", ";
  }
}
