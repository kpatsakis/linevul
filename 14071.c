bool VectorContains(const std::vector<std::string>& data,
                    const std::string& str) {
  return std::find(data.begin(), data.end(), str) != data.end();
}
