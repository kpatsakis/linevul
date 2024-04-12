static std::string SafeString(const char* s) {
  return s ? std::string(s) : std::string();
}
