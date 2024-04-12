void WriteString16ToPickle(Pickle& pickle, int* bytes_written, int max_bytes,
                           const string16& str) {
  int num_bytes = str.size() * sizeof(char16);
  if (*bytes_written + num_bytes < max_bytes) {
    *bytes_written += num_bytes;
    pickle.WriteString16(str);
  } else {
    pickle.WriteString16(string16());
  }
}
