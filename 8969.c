size_t PDFiumEngine::FindTextIndex::IncrementIndex() {
  DCHECK(valid_);
  return ++index_;
}
