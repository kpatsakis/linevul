static bool TokenExitsInSelect(const CompactHTMLToken& token) {
  const String& tag_name = token.Data();
  return ThreadSafeMatch(tag_name, inputTag) ||
         ThreadSafeMatch(tag_name, keygenTag) ||
         ThreadSafeMatch(tag_name, textareaTag);
}
