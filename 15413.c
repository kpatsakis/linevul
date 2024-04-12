Range* Document::createRange() {
  return Range::Create(*this);
}
