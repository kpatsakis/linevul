void SparseHistogram::WriteAscii(std::string* output) const {
  WriteAsciiImpl(true, "\n", output);
}
