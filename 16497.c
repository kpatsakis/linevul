bool Extension::ProducePEM(const std::string& input, std::string* output) {
  DCHECK(output);
  return (input.length() == 0) ? false : base::Base64Encode(input, output);
}
