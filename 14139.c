String Location::hostname() const {
  return DOMURLUtilsReadOnly::hostname(Url());
}
